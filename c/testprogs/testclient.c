#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#define PORT 8800
/* REPLACE with your server machine name*/
#define HOST "localhost"
#define DIRSIZE 8192
#define HOSTNMSZ 100

#define CONNECT_WAIT_INTERVAL 2

/*
 * Connect to Server and do some interaction over socket.
 */
main(argc, argv)
	int argc; char **argv;
{
	char hostname[HOSTNMSZ];
	char dir[DIRSIZE];
	int sd;
	int i;
	struct sockaddr_in sin;
	struct sockaddr_in pin;
	struct hostent *hp;
	int r;

	if (argc < 2) {
		printf("usage: testclient <data to send> [<this machine's name>]\n");
		exit(-1);
	}
	strncpy(hostname,HOST,sizeof(hostname));
	if (argc > 2)
		strcpy(hostname,argv[2]);
	/* go find out about the desired host machine */
	if ((hp = gethostbyname(hostname)) == 0) {
		perror("gethostbyname");
		exit(1);
	}
	/* fill in the socket structure with host information */
	memset(&pin, 0, sizeof(pin));
	pin.sin_family = AF_INET;
	pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	pin.sin_port = htons(PORT);

	while (1) {
		/* grab an Internet domain socket */
		if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
			perror("socket");
			exit(1);
		} 
		if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&i, sizeof(i))) {
			perror("set socket options");
			exit(1);
		}
		/* connect to PORT on HOST */
		r = connect(sd,(struct sockaddr *) &pin, sizeof(pin));
		if (r == 0) {
			printf("connected\n"); 
			/* send a message to the server PORT on machine HOST */
			if (send(sd, argv[1], strlen(argv[1]), 0) == -1) {
				perror("send");
				exit(1);
			}
			/* wait for a message to come back from the server */
			/*if (recv(sd, dir, DIRSIZE, 0) == -1) {
				perror("recv");
				exit(1);
			}*/
			/* spew-out the results and bail out of here! */
			printf("%s\n", dir);
			sleep(CONNECT_WAIT_INTERVAL/2);
		} else {
			perror("connect");
			printf("Retrying in %d seconds...\n", CONNECT_WAIT_INTERVAL);
			sleep(CONNECT_WAIT_INTERVAL);
		}
		close(sd);
	}
}

