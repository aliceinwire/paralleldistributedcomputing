#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stddef.h>

#include "../logger/logger.h"
#include "../../c/ds/list.h"
#include "../cluster/cluster.h"

/* Possible system state values */
#define SYS_BORN 0
#define SYS_CONNECTING 1
#define SYS_ON_CLUSTER 2
#define SYS_DISCONNECTING 3
#define SYS_IDLE 4

/* User option (menu) */
#define USROPT_PRINT_CLUSTER_NODES 1
#define USROPT_START_CLUSTER_FW 2
#define USROPT_STOP_NW 3
#define USROPT_SHUTDOWN_CLUSTER 4
#define USROPT_EXIT 5

static system_state = SYS_BORN;

static int get_sys_state()
{
	return system_state;
}

static void set_sys_state(const int s)
{
	if (s < 0 || s > SYS_IDLE)
		return;
	system_state = s;
}

static int sys_can_shutdown()
{
	if (system_state == SYS_ON_CLUSTER
	    || system_state == SYS_CONNECTING
	    || system_state == SYS_DISCONNECTING)
		return 0;
	return 1;
}

#define list_for_each(pos, head) \
        for (pos = (head)->next; pos != (head); pos = pos->next)

/**
 * container_of - cast a member of a structure out to the containing
 * structure
 * @ptr:        the pointer to the member.
 * @type:       the type of the container struct this is embedded in.
 * @member:     the name of the member within the struct.
 *
 */
#define container_of(ptr, type, member) ({ \
	 const typeof( ((type *)0)->member ) *__mptr = (ptr); \
		  (type *)( (char *)__mptr - offsetof(type,member) );})

/**
 * list_entry - get the struct for this entry
 * @ptr:        the &struct list_head pointer.
 * @type:       the type of the struct this is embedded in.
 * @member:     the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
                container_of(ptr, type, member)

struct machine_node {
        unsigned int 	sockfd;
        unsigned int 	port;
	unsigned char 	name[28];	/* adjusted to power of 2 */
        unsigned char 	ip_add[16];
        struct 		list_head nodes;
};

#endif
