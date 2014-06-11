#ifndef COMMON_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printarr(int *arr, int len)
{
	int i = 0;

	for (; i < len; i++)
		printf("arr[%d] = %d\n", i, arr[i]);
	printf("====================\n");
}

void fillarr(int arr[], int len)
{
	int i = 0;

	printf("Filling array with %d random integers.\n", len);
	for (; i < len; ++i)
		arr[i] = rand();
}

void swap(int *first, int *second)
{
	*first = *first + *second;
	*second = *first - *second;
	*first = *first - *second;
}

int print_time_diff(time_t cache)
{
	time_t curr;
	int diff = 0;

	time(&curr);
	diff = curr - cache;
	printf("Time elapsed = %d seconds\n", diff);
	return diff;
}

#endif
