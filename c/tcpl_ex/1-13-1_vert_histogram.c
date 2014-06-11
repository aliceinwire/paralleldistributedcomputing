#include <stdio.h>
#include <string.h>
#define BUFLEN 256 
#define TOKLEN 32 

unsigned int find_max(unsigned int *table, unsigned int bars)
{
	unsigned int max = 0;
	unsigned int i;

	for (i = 0; i < bars; ++i)
		if (max < table[i])
			max = table[i];
	return max; 
}

unsigned int fill_lookup_tab(const char *buf, unsigned int *lookup)
{
	char c;
	unsigned int itok = 0;
	unsigned int len = 0;

	while (c = *buf++) {
		if (c == ' ' || c == '\t' || c == '\n') {
			lookup[itok++] = len;
			len = 0;
		} else
			++len;
	}
	return itok;
}

void print_lower_boundary(unsigned int bars)
{
	printf("***\t");
	while (bars--)
		printf("  =  ");
	printf("\n");
}

void dump_lookup(unsigned int *lookup, unsigned int bars)
{
	unsigned int i;

	for (i = 0; i < bars; ++i)
		printf("lookup[%d]\t-%d-\n", i, lookup[i]);
}

void display_vert_histogram(unsigned int * lookup, unsigned int bars)
{
	unsigned int i, j;
	unsigned int max = find_max(lookup, bars);
	unsigned int height = max;

	printf("Max in lookup is: %d\n", height); 
	for (i = height; i > 0; --i) {
		printf("(%d)\t", i);
		for (j = 0; j < bars; ++j)
			if (i <= lookup[j])
				printf("  *  ");
			else 
				printf("     ");
		printf("\n");
	}
	if (height)
		print_lower_boundary(bars);
}

void print_vert_histogram(const char *buf, unsigned int *lookup)
{
	unsigned int bars = fill_lookup_tab(buf, lookup);
	display_vert_histogram(lookup, bars);
}

int main(int argc, char **argv)
{
	char buf[BUFLEN] = {'\0'};
	unsigned int lookup[BUFLEN] = {'\0'};

	printf("Please enter some text: ");
	if (!fgets(buf, BUFLEN, stdin)) {
		printf("Unable to read from input stream.");
		return -1;
	} 
	printf("You have entered: %s", buf);
	print_vert_histogram(buf, lookup);
	return 0;
}

