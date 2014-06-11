#include <stdio.h>
/* count lines in input; 2nd version */
main()
{
	int c, nl;
	double nc;

	nl = 0;
	for (nc = 0; (c = getchar()) != EOF; ++nc)
		if (c == '\n')
			++nl;
	printf("%.0f, l = %d\n", nc, nl);
}

