#include "../common/common.h"
#include "fcntl.h"

#if !defined (_LOGGER_H_)
#define _LOGGER_H_

#define MAX_LOG 80

enum g_logleveltab {
	EMERG,			/* Emergency */
	ERROR,
	INFOR,			/* Informatory */
	DEBUG,
	TRACE
};

static unsigned short g_loglevel = 4;	/* Logging level - system wide. */
static int g_loggerfd = -1;	/* Logger file descriptor. */
static char *g_logfilepath = "./log/main.log";	/* Global logfile path. */
void logmsg(const unsigned short, char *fmat, ...);

#endif				/* #define _LOGGER_H_ */
