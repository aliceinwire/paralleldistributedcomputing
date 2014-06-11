#ifndef BUBBLE_H

void bubblesimple(int arr[], int len)
{
	int i, j;

	for (i = 0; i < len; ++i)
		for (j = 0; j < len - 1; ++j)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}

void bubblerevopt(int arr[], int len)
{
	int i, j;

	for (i = len - 1; i >= 0; --i)
		for (j = 0; j < i; ++j)
			if (arr[j] > arr[j + 1])
				swap(&arr[j], &arr[j + 1]);
}

void bubbleswapflagopt(int arr[], int len)
{
	int i, swapped = 0;

	do {
		swapped = 0;
		for (i = 0; i < len; ++i)
			if (arr[i] > arr[i + 1]) {
				swap(&arr[i], &arr[i + 1]);
				swapped = 1;
			}
	} while (swapped);
}

#endif
