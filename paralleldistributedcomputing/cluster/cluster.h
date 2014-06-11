#ifndef _CLUSTER_H
#define _CLUSTER_H

#include "../net/net.h"

static unsigned int nr_peers = 0;

/*
 * CALLBACKS: These functions will be invoked by the network layer in event of
 * activity on network.
 */
static void callb_accept(void *p);
static void callb_conn(void *p);
static void callb_recv(void *p);
static void callb_discon(void *p);

/*
 * The actual network layer threads, controlled by the cluster logic.
 */
pthread_t listener;
pthread_t talker;
pthread_t walker;

/*
 * Important when synchronizing the shutdown sequence of the cluster node.
 */
static unsigned int shutting_down = 0;

void print_cluster_nodes();

/*
 * A doubly linked list - the node tree
 */
static LIST_HEAD(nodetree);

#endif
