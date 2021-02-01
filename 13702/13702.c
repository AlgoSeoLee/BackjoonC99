#include <stdio.h>

typedef int (*BinarySearchComparator)(int* arr, int target, int mid, void* args);
int BinarySearch(int* arr, int target, int length, BinarySearchComparator func, void* args) {
	int start = 1;
	int end = length;

	int result = 0;
	int comp = 0;
	while (start <= end) {
		int mid = (start + end) / 2;
		int current = func(arr, target, mid, args);

		if (current) {
			if (current >= comp && mid >= result) {
				comp = current;
				result = mid;
			}
			start = mid + 1;
		} else
			end = mid - 1;
	}

	return result;
}

int CalcBeer(int* beers, int order, int amount, void* args) {
	int person = *(int*)args;

	int i, c = 0;
	for (i = 0; i < order; i++)
		c += beers[i] / amount;

	if (c >= person)
		return c;

	return 0;
}

int main() {
	int order, person;
	scanf("%d %d", &order, &person);

	int i, beers[10000], max = 0;
	for (i = 0; i < order; i++) {
		scanf("%d", beers+i);
		if (beers[i] > max)
			max = beers[i];
	}

	int result = BinarySearch(beers, order, max, CalcBeer, &person);
	printf("%d\n", result);
}
