/* 
 * The actual socket level interaction.
 * Invoke cluster routines on specific signals from network.
 * Also, handle communication between nodes (at the wire level).
 */
#include "net.h"

/*
 * Declare that this thread can be cancelled,
 * but cancelation is defered until 
 * cancelation point is hit.
 */
void set_thread_attributes(void)
{
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
}

void cleanup_sockets(void *args)
{
	if (!args)
		return;
	shutdown(*(int *) args, SHUT_RDWR);
}

/* 
 * Infintely loop, listening for cluster traffic and notify cluster layer of
 * incoming calls.
 */
void *nwkeep_listening(void *p)
{
	unsigned int lsock;
	unsigned int asock;
	unsigned int sockopt = 1;
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	socklen_t len = sizeof(pin);
	socklen_t slen = sizeof(sockopt);

	set_thread_attributes();

	/* combined flags avoid calls to fcntl :) */
	lsock = socket(AF_INET, SOCK_STREAM /*| SOCK_NONBLOCK */ , 0);
	if (lsock < 0) {
		perror("socket error!");
		goto term_thread;
	}

	/* fill in local info in sockaddr */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(PORT);

	if (setsockopt(lsock, SOL_SOCKET, SO_REUSEADDR, &sockopt, slen) <
	    0) {
		perror("setsockopt error!");
		goto term_thread;
	}
	if (bind(lsock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		perror("bind error!");
		goto term_thread;
	}
	if (listen(lsock, CONN_BKLOG) < 0) {
		perror("listen error!");
		goto term_thread;
	}
	pthread_cleanup_push(cleanup_sockets, &lsock);
	while (!shutting_down) {
		asock = accept(lsock, (struct sockaddr *) &pin, &len);
		if (asock < 0) {
			perror("initial accept error!");
			goto term_thread;
		}
		if (errno == EAGAIN || errno == EWOULDBLOCK) {
			sleep(1);
			continue;
		}
		callbacks[CB_ACCEPTED] (&pin);
		close(asock);
		pthread_testcancel();
	}
	pthread_cleanup_pop(cleanup_sockets);
      term_thread:
	close(lsock);
	close(asock);
	pthread_exit(NULL);
}

/* 
 * Infintely loop, talking to other cluster nodes and notify cluster layer of
 * successful connections.
 */
void *nwkeep_talking(void *p)
{
	unsigned int lsock;
	unsigned int asock;
	size_t len = 0;
	struct sockaddr_in sin;

	set_thread_attributes();

	lsock = socket(AF_INET, SOCK_STREAM, 0);
	if (lsock < 0) {
		perror("socket error!");
		goto term_thread;
	}
	/* fill in local info in sockaddr */
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(PORT + 1);

	if (bind(lsock, (struct sockaddr *) &sin, sizeof(sin)) < 0) {
		perror("bind error!");
		goto term_thread;
	}
	while (!shutting_down) {
		sleep(1);
		callbacks[CB_CONNECTED] (NULL);
		pthread_testcancel();
	}
      term_thread:
	close(lsock);
	pthread_exit(NULL);
}

/* 
 * Infintely loop, walking to other cluster nodes and notify cluster layer of
 * broken connections.
 */
void *nwkeep_walking(void *p)
{
        struct list_head *pos = NULL;
        struct machine_node *n = NULL;
	int r = 0;
	char buff[80] = { '\0' };

	set_thread_attributes();

	while (!shutting_down) {
		sleep(10);	/* This interval is very crucial, it is O(n). */
		printf("\nChecking status of lines...\n");
		list_for_each(pos, &nodetree) {
			memset(buff, 0, sizeof(buff));
			n = list_entry(pos, struct machine_node, nodes);
			printf("\nChecking conn to %s - %d\n", n->name, n->port); 
			r = read(n->sockfd, buff, sizeof(buff));
			if (r < 0)
				callbacks[CB_DISCON] (NULL);
			printf("\nData ready!\n");
		}
		pthread_testcancel();
	}
      term_thread:
	pthread_exit(NULL);
}
