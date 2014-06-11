#include <stdio.h>
#include <string.h>

#define BUFLEN 128
#define MAX_TOKENS 128

unsigned int tokenize(const char *buf, const char sep, char **tokens, 
						unsigned int num)
{
	unsigned int ntok = 0;
	char currtok[BUFLEN] = {'\0'};
	char *c = currtok;

	if (!buf || !tokens || !num)
		return;
	while (*buf) {
		if (*buf == sep) {
			printf("[%d]\t%s\n", ntok, currtok);
			strncpy(tokens[ntok], currtok, BUFLEN);
			printf("[added token to %d location]", ntok);
			memset(currtok, 0, BUFLEN);
			c = currtok;
			++buf;
			++ntok;
			continue;
		}
		*c++ = *buf++; 
	}
	return ntok;
}

void print_tokens(const char *tokens[], unsigned int num)
{
	unsigned int i = 0;

	if (!*tokens || !num)
		return; 
	for (; i < num; ++i)
		printf("[%d]\t%s\n", i, tokens[i]);
}

void init_tokens(char *tokens[], unsigned int num)
{
	unsigned int i = 0;

	if (!*tokens || !num)
		return;
	for (; i < num; ++i)
		memset(tokens[i], 0, sizeof(tokens[i]));
}

int main()
{
	char sep;
	char buf[BUFLEN];
	char tokens[MAX_TOKENS][BUFLEN];
	unsigned int ntok = 0;

	memset(buf, 0, sizeof(buf));
	init_tokens(tokens, MAX_TOKENS);
	printf("Enter string: ");
	if (!fgets(buf, BUFLEN, stdin))
		return -1;
	printf("Enter separator char: ");
	sep = getchar();
	printf("You entered string: %s\nseparator: %c\n", buf, sep);
	ntok = tokenize(buf, sep, tokens, MAX_TOKENS);
	printf("You have: %d tokens\n", ntok);
	if (ntok)
		print_tokens(tokens, MAX_TOKENS);
	return 0;
}

