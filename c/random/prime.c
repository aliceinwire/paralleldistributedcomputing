#include <stdio.h>

main()
{
	int num, i;

	printf("Enter a number: ");
	scanf("%d", &num);
	for (i = 2; i <= num / 2; ++i)
		if (num % i == 0) {
			printf("%d is NON-PRIME\n", num);
			return;
		}
	printf("%d is PRIME\n", num);
}

