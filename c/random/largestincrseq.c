#include <stdio.h>
#include <string.h>

#define ARRAY_LEN 10

void generate_random_seq(int *arr, int len)
{
	int counter = 0;

	printf("Will populate a random sequence now\n");
	while (counter < len)
		arr[counter++] = random();
}

void accept_seq(int *arr, int len)
{
	int counter = 0;

	printf("Will accept the sequence now\n");
	while (counter < len) {
		printf("(%d) >> ", counter + 1);
		scanf("%d", &arr[counter]);
		++counter;
	} 
}

void print_seq(int *arr, int len)
{
	int counter = 0;

	printf("Will print the sequence now\n");
	printf("start");
	while (counter < len) {
		printf(", %d", arr[counter]);
		++counter;
	}
	printf(", end of sequence\n");
}

int largest_incr_subseq(int *arr, int len)
{
	int bestcnt = 1, cnt = 1, i, j, k, last;

	for (i = 0; i < len; ++i) {
		for (j = i + 1; j < len; ++j) {
			cnt = 1;
			last = arr[i];
			printf("\n%d", arr[i]);
			for (k = j; k < len; ++k) {
				if (last < arr[k]) {
					printf(", %d", arr[k]);
					last = arr[k];
					++cnt;
				}
			}
			if (bestcnt < cnt)
				bestcnt = cnt;
		}
		if (bestcnt > (len - i))
			break; 
	}
	return bestcnt;
}

int lis(int *arr, unsigned int len)
{
	unsigned int i, j, k;
	unsigned int cnt, max = 0;
	int last;

	for (i = 0; i < len; ++i) {
		cnt = 1;
		for (j = i+1; j < len; ++j) {
			if (arr[i] <= arr[j]) {
				printf(", %d", arr[j]);
				++cnt;
				for (k = j+1; k < len; ++k) {
					if (arr[j] <= arr[k]) {
						last = arr[k];
						printf(", %d", arr[k]);
						++cnt;
					}
				}
			}
		}		
		printf("Count for arr[i]: %d", cnt);
		if (max < cnt)
			max = cnt;
	}
	return max;
}

int main(int argc, char **argv)
{
	int arr[ARRAY_LEN] = {0};

	printf("Given a sequence of integers, this program finds the largest" \
			"increasing subsequence.\n");
	//generate_random_seq(arr, ARRAY_LEN);
	accept_seq(arr, ARRAY_LEN);
	print_seq(arr, ARRAY_LEN); 
	largest_incr_subseq(arr, ARRAY_LEN); 
	printf("\nThe length of largest increasing sequence is %d\n", largest_incr_subseq(arr, ARRAY_LEN)); 
	return 0;
}

