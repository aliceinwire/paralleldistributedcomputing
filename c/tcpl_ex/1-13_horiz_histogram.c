#include <stdio.h>
#include <string.h>
#define BUFLEN 256 
#define TOKLEN 32 

void print_horiz_histogram(char *buf)
{
	char c;
	char token[TOKLEN] = {'\0'};
	unsigned int itok = 0;

	printf("|");
	while (c = *buf++) {
		if (c == ' ' || c == '\t' || c == '\n') {
			itok = 0;
			memset(token, 0, TOKLEN);
			printf(">\n|");
		} else {
			printf("=");
			token[itok++] = c;
		}
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	char buf[BUFLEN] = {'\0'};

	printf("Please enter some text: ");
	if (!fgets(buf, BUFLEN, stdin)) {
		printf("Unable to read from input stream.");
		return -1;
	} 
	printf("You have entered: %s", buf);
	print_horiz_histogram(buf);
	return 0;
}
