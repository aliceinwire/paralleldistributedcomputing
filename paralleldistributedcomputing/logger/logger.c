#include "logger.h"

/*
 * Check whether the logger file is alright. 
 */
static inline int fileok()
{
	if (g_loggerfd != -1)
		return g_loggerfd;
	g_loggerfd = open(g_logfilepath, O_CREAT | O_WRONLY | O_APPEND);
	return g_loggerfd >= 0;
}

/*
 * Core of the logger.
 */
void logmsg(const unsigned short loglevel, char *fmt, ...)
{
	if (!fmt)
		return;
	if (g_loglevel >= loglevel) {
		printf("%s", fmt);
		if (!fileok())
			return;
		if (write(g_loggerfd, fmt, strlen(fmt)) < 0)
			perror("logger");
	}
}
