/* 
 * This program takes 1 input; text file name containing a base 10 integer in
 * string format.
 */
#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>

#define ARGPOSFILE 1
#define BUFSIZE 32

unsigned int readfile(char *fname)
{
	unsigned int fd = 0;
	int num = 0;
	size_t n = 0;
	char buf[BUFSIZE] = {'\0'};

	if (!fname)
		goto FAILEDREAD;
	if ( (fd = open(fname, O_RDONLY)) == -1) {
		perror("readfile failed");
		goto FAILEDREAD;
	}
	if ( (n = read(fd, buf, BUFSIZE-1)) <= 0) {
		perror("reading from file failed");
		goto FAILEDREAD;
	}
	if ( (num = atoi(buf)) > 0)
		return num;
	FAILEDREAD:
		return 0;
}

void hoppityhop(unsigned int num)
{
	unsigned int i = 1, rem5 = 0, rem3 = 0;

	for (; i <= num; ++i) { 
		rem5 = i%5;
		rem3 = i%3; 
		if (rem5 == 0 && rem3 == 0)
			printf("Hop\n");
		else if (rem5 == 0)
			printf("Hophop\n");
		else if (rem3 == 0)
			printf("Hoppity\n");
	}
}

int main(int argc, char **argv)
{
	unsigned int num, i = 1;

	if (argc < 2)
		return -1;
	num = readfile(argv[ARGPOSFILE]);
	printf("NUMBER = %u, hit enter", num);
	getchar();
	hoppityhop(num);
	return 0; 
}

