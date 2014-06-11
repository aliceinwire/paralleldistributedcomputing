#ifndef _NET_H
#define _NET_H

#include <sys/socket.h>
#include <netdb.h>

#include "../common/common.h"
#include "../cluster/cluster.h"

#define PORT 8800
#define CONN_BKLOG 5

#define NUM_CALLB 4		/* number of callback functions available in the cluster layer */

#define CB_ACCEPTED     0x00000000
#define CB_CONNECTED    0x00000001
#define CB_RECEIVED	0x00000010
#define CB_DISCON	0x00000011

void *nwkeep_listening(void *);
void *nwkeep_talking(void *);
void *nwkeep_walking(void *);

/*
 * This is the array of funtion pointers, which will hold functions to be
 * invoked in the cluster layer. (by the network layer)
 */
void (*callbacks[NUM_CALLB]) (void *);

#endif
