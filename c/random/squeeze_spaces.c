#include <stdio.h>
#include <string.h>
#define STRLEN 256

void squeeze_spaces(char *string)
{
	unsigned int len = strlen(string), counter, inner;
	char temp;

	for (counter = 0; counter < len; ++counter) {
		if (string[counter] == ' ') {
			++counter;
			inner = counter;
			while (string[inner] == ' ')
				++inner;
			while (inner < len && string[inner] != ' ') {
				temp = string[counter];
				string[counter] = string[inner];
				string[inner] = temp;
				++inner;
				++counter;
			}
			--counter;
		}
	}
	string[counter] = '\0';
}

int main(int argc, char **argv)
{
	char input[STRLEN];

	printf("This program will sqeeze multiple WS to single at each " \
		"occurrence.\nEnter a string with white-spaces: ");
	memset(input, 0, STRLEN);
	fgets(input, STRLEN, stdin);
	printf("Squeezing spaces in the string...\n");
	squeeze_spaces(input);
	printf("After Squeezing spaces in the string, the string looks " \
		"like...\n");
	puts(input);
	return 0;
}

