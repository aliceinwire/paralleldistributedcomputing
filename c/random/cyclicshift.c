#include <stdio.h>

unsigned int cyclicshift(unsigned int num, unsigned int shiftby)
{
	unsigned int copy = num;

	return ( (num << shiftby) | (copy >> ( (sizeof(int)*8)
						-shiftby)) );
}

void printbinary(unsigned int num)
{
	unsigned int i = 0;

	for (; i < 32; ++i, num >>= 1)
		printf("%d", num & 1);
	printf("\n");
}

int main()
{
	int num = 3;

	printf("\ninput: %x: %u\n", num, num); 
	printbinary(num);
	num = cyclicshift(num, 2); 
	printf("\noutput: %x: %u\n", num, num);
	printbinary(num);
	return 0;
}
