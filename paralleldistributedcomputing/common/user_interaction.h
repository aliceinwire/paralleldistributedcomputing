#ifndef _USER_INTERACTION_H
#define _USER_INTERACTION_H

#include "common.h"

unsigned int get_user_selection()
{
	unsigned int i = 0;

	printf("\n\n==CLUSTER FRAMEWORK==\n");
	printf("1. List nodes in cluster.\n");
	printf("2. Start this node.\n");
	printf("3. Shutdown this node.\n");
	printf("4. Shutdown cluster.\n");
	printf("5. Exit.\n");
	printf("Please select your option: ");
	scanf("%d", &i);
	printf("Your option: %d\n", i);
	return i;
}

void start_user_interaction()
{
	do {
		switch (get_user_selection()) {
		case USROPT_PRINT_CLUSTER_NODES:
			print_all_cluster_nodes();
			break;
		case USROPT_START_CLUSTER_FW:
			start_cluster_fw();
			break;
		case USROPT_STOP_NW:
			stop_network();
			break;
		case USROPT_SHUTDOWN_CLUSTER:
			logmsg(TRACE,
			       "[STARTUP]:\tSHUTDOWN CLUSTER - WIP\n");
			break;
		case USROPT_EXIT:
			logmsg(TRACE, "[STARTUP]:\tEXIT\n");
			if (!sys_can_shutdown()) {
				printf
				    ("Cannot shutdown now, system in unstable \
					state, prefer shutting down \
					cluster/network before you try this \
					option\n");
				break;
			}
			return;
			break;
		default:
			logmsg(TRACE, "[STARTUP]:\tinvalid input\n");
			break;
		}
	} while (1);
}

#endif
