#include <stdio.h>

static unsigned int counter = 0;

void makerupee(int amt, unsigned int fives, unsigned int tens,
					unsigned int twenties)
{
	++counter;
	if (amt == 0) {
		printf("%d - %d - %d = %d\n", fives, tens, twenties,
			fives*5 + tens*10 + twenties*20);
		return;
	}
	if (amt < 0)
		return;
	makerupee(amt-5, fives+1, tens, twenties);
	makerupee(amt-10, fives, tens+1, twenties);
	makerupee(amt-20, fives, tens, twenties+1);
}

int main(int argc, char **argv)
{
	if (argc < 2) {
		printf("I need a value to sum up to.\n");
		return -1;
	} 
	makerupee(atoi(argv[1]), 0, 0, 0);
	printf("I recursed %d times!!!\n", counter);
	return 0;
}

