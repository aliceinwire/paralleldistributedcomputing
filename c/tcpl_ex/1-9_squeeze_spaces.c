#include <stdio.h>

main()
{
	int c, inblanks;

	inblanks = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (!inblanks)
				putchar(c);
			inblanks = 1;
		} else {
			inblanks = 0; 
			putchar(c);
		}
	}
}

