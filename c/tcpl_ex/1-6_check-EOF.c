#include <stdio.h>

main()
{
	int c;

	printf("Enter text, ctrl+d to stop\n");
	while (c = (getchar() != EOF))
		printf("c = %d; Inside while\n", c);
	printf("c = %d; Outside while\n", c);
}

