#include <stdio.h>
#include <string.h>

unsigned int is_palindrome(const char *s)
{
	const char *e = NULL;

	if (!s)
		return 1;
	e = s + (strlen(s)-1);
	if (s == e)
		return 1;
	while (s < e)
		if (*s++ != *e--)
			return 0;
	return 1;
}

int main (int argc, char **argv)
{
	if (argc < 0)
		printf("palidrome program requires an input string."); 
	if (is_palindrome(argv[1]))
		printf("%s is a palidrome.\n", argv[1]);
	else
		printf("%s is not a palidrome.\n", argv[1]);
	return 0;
}

