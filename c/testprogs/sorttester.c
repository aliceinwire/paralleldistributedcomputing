#include "../sorts/intarrs/common.h"
#include "../sorts/intarrs/bubblesort.h"
#include "../sorts/intarrs/selectionsort.h"
#include "../sorts/intarrs/insertionsort.h"

int main(int argc, char **argv)
{
	time_t cache;
	int i, len =  (argc > 1) ? atoi(argv[1]) : 10, arr[len];
	int bubblesimp, bubbleropt, bubbleswpflgopt;
	int selectionsimple, selectionmodmin;
	int insertion;
	
	fillarr(arr, len);
	printf("Bubble Sort - plain\n");
	time(&cache);
	bubblesimple(arr, len);
	bubblesimp = print_time_diff(cache);
	printarr(arr, len);

	fillarr(arr, len);
	printf("Bubble Sort - reverse counter optimized\n");
	time(&cache);
	bubblerevopt(arr, len);
	bubbleropt = print_time_diff(cache);
	printarr(arr, len);

	fillarr(arr, len);
	printf("Bubble Sort - swap flag optimized\n");
	time(&cache);
	bubbleswapflagopt(arr, len);
	bubbleswpflgopt = print_time_diff(cache);
	printarr(arr, len);
	
	fillarr(arr, len);
	printarr(arr, len);
	printf("Selection Sort - plain\n");
	time(&cache);
	selectionsortsimple(arr, len);
	selectionsimple = print_time_diff(cache);
	printarr(arr, len);

	fillarr(arr, len);
	printf("Selection Sort Modular Min- plain\n");
	time(&cache);
	selectionsort(arr, len);
	selectionmodmin = print_time_diff(cache);
	printarr(arr, len);

	fillarr(arr, len);
	printf("Insertion Sort - plain\n");
	time(&cache);
	insertionsort(arr, len);
	insertion = print_time_diff(cache);
	printarr(arr, len);

	printf("\nBUBBLE:\nsimple = %d, revopt = %d, swapflagopt = %d\n", bubblesimp, bubbleropt, bubbleswpflgopt);
	printf("\nSELECTION:\nselectionsimple = %d, selectionmodmin = %d\n", selectionsimple, selectionmodmin);
	printf("\nINSERTIION:\ninsertion = %d\n\n", insertion);
	return 0;
}

