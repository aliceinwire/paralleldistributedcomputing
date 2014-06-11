#ifndef INSERTION_H

void insertionsort(int arr[], int len)
{
	int i = 1, j, cached;

	if (len < 2)
		return; 
	for (; i < len; ++i) {
		cached = arr[i];
		for (j = i - 1; j >= 0; --j) {
			if (arr[j] <= cached)
				break;
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = cached;
	}
}

#endif
