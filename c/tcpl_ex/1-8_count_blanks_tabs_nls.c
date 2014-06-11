#include <stdio.h>

main()
{
	int c, nls, tabs, blanks;
	double nc;

	nc = 0;
	nls = tabs = blanks = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ')
			++blanks;
		if (c == '\t')
			++tabs;
		if (c == '\n')
			++nls;
		++nc;
	}
	printf("blanks = %d, tabs = %d, lines = %d, chars = %6.0f\n", blanks,
								tabs, nls, nc);
}
