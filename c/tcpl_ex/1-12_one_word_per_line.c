#include <stdio.h>

#define IN 1
#define OUT 0

main()
{
	int c;
	unsigned int state = OUT;

	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == OUT)
				putchar('\n');
			state = IN;
		} else {
			state = OUT;
			putchar(c);
		}
	}
}

