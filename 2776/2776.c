#include <stdio.h>
#include <stdlib.h>

int comparator(const void* pa, const void* pb) {
	const int* a = pa;
	const int* b = pb;

	if (*a < *b)
		return -1;
	else if (*a > *b)
		return 1;

	return 0;
}

int binarySearch(int* arr, size_t length, int target) {
	size_t cursor = length / 2;
	size_t start = 0;
	size_t end = length;

	while (1) {
		if (end - start == 0)
			return -1;
		else if (cursor >= length)
			return start < length && arr[start] == target ? start : -1;

		int current = arr[cursor];
		if (target == current)
			return cursor;
		else if (target < current)
			end = cursor;
		else
			start = cursor + 1;

		cursor = start + cursor / 2;
	}
}

int main() {
	int c;
	scanf("%d", &c);

	while (c--) {
		int note1_length;
		scanf("%d", &note1_length);
		int note1[1000001];

		int i;
		for (i = 0; i < note1_length; i++)
			scanf("%d", note1 + i);

		qsort(note1, note1_length, sizeof(int), comparator);

		int note2_length;
		scanf("%d", &note2_length);
		int target;
		for (i = 0; i < note2_length; i++) {
			scanf("%d", &target);

			if (binarySearch(note1, note1_length, target) >= 0)
				printf("1\n");
			else
				printf("0\n");
		}
	}
}
