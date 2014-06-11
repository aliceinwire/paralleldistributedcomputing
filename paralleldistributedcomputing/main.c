#include "common/user_interaction.h"

void start(void)
{
	start_user_interaction();
}

int main(int argc, char **argv)
{
	logmsg(TRACE, "[MAIN]\tEntering main\n");
	start();
	return 0;
}
