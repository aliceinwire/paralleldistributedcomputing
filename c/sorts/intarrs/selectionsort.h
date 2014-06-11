#ifndef SELECTION_H

int minidx(int arr[], const unsigned int len, int minval)
{
	int i = 0, midx = -1;

	for (; i < len; ++i) {
		if (arr[i] < minval) {
			minval = arr[i];
			midx = i;
		} 
	}
	return midx;
}

void selectionsort(int arr[], const unsigned int len)
{
	int i = 0, minpos;

	for (; i < len; ++i) {
		minpos = i + minidx(arr + i + 1, len - i - 1, arr[i]) + 1;
		if (minpos != i)
			swap(&arr[i], &arr[minpos]);
	}
}

void selectionsortsimple(int arr[], const unsigned int len)
{
	int i = 0, j, minpos, tmp;

	for (; i < len; ++i) {
		minpos = i;
		for (j = i + 1; j < len; ++j)
			if (arr[j] < arr[minpos])
				minpos = j;
		if (minpos != i)
			swap(&arr[i], &arr[minpos]);
	}
}

#endif

