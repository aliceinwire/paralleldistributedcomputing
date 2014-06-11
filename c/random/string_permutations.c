#include <stdio.h>

unsigned int counter;

void swap(char *string, unsigned int x, unsigned int y)
{
	unsigned int len = 0;
	char tmp;
	
	if (!string)
		return;
	len = strlen(string);
	if (x > len || y > len)
		return;
	tmp = string[x];
	string[x] = string[y];
	string[y] = tmp;
}

void permute(char *string, unsigned int len, unsigned int fixed)
{
	unsigned int i;

	if (fixed == len-1) {
		printf("\n[%d]: %s", ++counter, string);
		return;
	}
	for (i = fixed; i < len; ++i) {
		swap(string, i, fixed);
		permute(string, len, fixed+1); 
		swap(string, i, fixed);	
	} 
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("I need a string to permute.\n");
		return -1;
	} 
	permute(argv[1], strlen(argv[1]), 0);
	printf("\nI recursed %d times!!!\n", counter);
	return 0;
}

