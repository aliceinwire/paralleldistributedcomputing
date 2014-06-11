#include <stdio.h>

int main(int argc, char **argv)
{
	printf("Data type sizes for this platform:\n");

	printf("char\t:\t%d\n", sizeof(char));
	printf("int\t:\t%d\n", sizeof(int));
	printf("unsigned int\t:\t%d\n", sizeof(unsigned int));
	printf("long unsigned int\t:\t%d\n", sizeof(long unsigned int));
	printf("long\t:\t%d\n", sizeof(long));
	printf("float\t:\t%d\n", sizeof(float));
	printf("double\t:\t%d\n", sizeof(double));
	printf("long long\t:\t%d\n", sizeof(long long));

	return 0;
}
