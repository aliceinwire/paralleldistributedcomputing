/* 
 * Actual cluster logic is implemented in this layer.
 * Regulates the network layer with the use of callback methods.
 */
#include "cluster.h"

void print_all_cluster_nodes()
{
	struct list_head *pos = NULL;
	struct machine_node *n = NULL;

	if (!nr_peers) {
		printf("No clients connected yet.\n");
		return;
	}
	list_for_each(pos, &nodetree) {
		n = list_entry(pos, struct machine_node, nodes);
		printf("\n\t%d - %s\n", n->port, n->name);
	}
}

void clear_cluster_nodes_list()
{
	if (!nr_peers)
		return;
	//list_del_all(&nodetree);
}

/*
 * Notified when network layer recieves incoming calls.
 */
void callb_accept(void *p)
{
	struct sockaddr_in *s = (struct sockaddr_in *) p;
	struct machine_node *n = (struct machine_node *) malloc(sizeof(struct machine_node));

	if (!s || !n)
		return; 
	n->nodes.prev = n->nodes.next = &n->nodes;
	memset(n->name, 0, strlen(n->name));
	/*strncpy((char *)&n->name, (char *)inet_ntoa(s->sin_addr),
	   sizeof(n->name)-1); */
	//printf("\nconnected with: %s", (char *)inet_ntoa(s->sin_addr));
	n->port = ntohs(s->sin_port);

	++nr_peers;
	list_add_tail(&n->nodes, &nodetree);
}

/*
 * Notified when network layer is able to connect to a server.
 */
void callb_conn(void *p)
{
	if (!p)
		return;
	printf("connected to server!\n");
}

/*
 * Notified when network layer has got a broken relation :(.
 */
void callb_discon(void *p)
{
	printf("Client conn broken\n");
	--nr_peers;
	if (!p)
		return;
}

/*
 * Notified when network layer recieves signals.
 */
void callb_recv(void *p)
{
	if (!p)
		return;
}

/*
 * Register callbacks with network layer. Wire up the framework.
 */
int reg_net_callbs(void)
{
	logmsg(TRACE, "[CLUSTER]:\tSetting up callback routines\n");
	callbacks[CB_ACCEPTED] = callb_accept;
	callbacks[CB_CONNECTED] = callb_conn;
	callbacks[CB_RECEIVED] = callb_recv;
	callbacks[CB_DISCON] = callb_discon;
	logmsg(TRACE,
	       "[CLUSTER]:\tNetwork callback routines registered\n");
	return 0;
}

/*
 * Disabling the callbacks. Crude method! Do NOT use do this unless you are
 * sure that framework is unwired. Else this is fatal...
 */
void clear_net_callbs(void)
{
	memset(callbacks, 0, sizeof(callbacks));
}

int start_network(void)
{
	int r;

	r = pthread_create(&listener, NULL, nwkeep_listening, NULL);
	if (r) {
		logmsg(EMERG,
		       "[CLUSTER]: Cannot spawn listener thread!\n");
		goto out;
	}
	r = pthread_create(&talker, NULL, nwkeep_talking, NULL);
	if (r) {
		logmsg(EMERG, "[CLUSTER]: Cannot spawn talking thread!\n");
		goto out;
	}
	r = pthread_create(&walker, NULL, nwkeep_walking, NULL);
	if (r) {
		logmsg(EMERG, "[CLUSTER]: Cannot spawn walking thread!\n");
		goto out;
	}
	logmsg(TRACE, "[CLUSTER]:\tNetwork threads are functional\n");
      out:
	return r;
}

/*
 * Initialize cluster framework. This function is immune to multiple
 * invocations.
 */
int start_cluster_fw(void)
{
	int r = 0;

	if (get_sys_state() == SYS_ON_CLUSTER) {
		logmsg(TRACE,
		       "[CLUSTER]:\tThis node is already on cluster\n");
		goto out;
	}
	if (get_sys_state() == SYS_CONNECTING
	    || get_sys_state() == SYS_DISCONNECTING) {
		logmsg(TRACE,
		       "[CLUSTER]:\tCluster layer is busy, retry\n");
		goto out;
	}
	set_sys_state(SYS_CONNECTING);
	r = reg_net_callbs();
	if (r) {
		logmsg(ERROR, "[CLUSTER]:\tCluster layer cannot register \
				callbacks in n/w layer\n");
		goto out;
	}
	r = start_network();
	if (r) {
		logmsg(ERROR,
		       "[CLUSTER]:\t n/w layer refuses to come up\n");
		goto out;
	}
	set_sys_state(SYS_ON_CLUSTER);
	logmsg(TRACE, "[CLUSTER]:\tCluster layer is UP now\n");
      out:
	return r;
}

/*
 * Bring down the network layer threads. Wait forever for the n/w layer
 * threads.
 */
int stop_network()
{
	int r = 0;
	shutting_down = 1;
	if (get_sys_state() != SYS_ON_CLUSTER) {
		logmsg(ERROR,
		       "[CLUSTER]:\tSystem not connected to cluster\n");
		r = -1;
		goto out;
	}
	set_sys_state(SYS_DISCONNECTING);
	logmsg(TRACE, "[CLUSTER]:\tSignalling network layer to go DOWN\n");
	pthread_cancel(listener);
	pthread_cancel(talker);
	pthread_cancel(walker);
	/*
	 * Give time to the terminating threads since they are handling pthread
	 * cancel requests in a defered manner.
	 */
	logmsg(TRACE, "[CLUSTER]:\tWaiting for network threads...\n");
	pthread_join(listener, NULL);
	pthread_join(talker, NULL);
	pthread_join(walker, NULL);
	logmsg(TRACE, "[CLUSTER]:\tNetwork layer down\n");
	set_sys_state(SYS_IDLE);
      out:
	return r;
}

void shutdown_cluster_fw(void)
{
	stop_network();
	clear_net_callbs();
}

void stop_cluster_fw(void)
{
	logmsg(TRACE, "[CLUSTER]:\tCluster layer is going to cease now\n");
	stop_network();
}
