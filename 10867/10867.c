#include <stdio.h>
#include <stdlib.h>

int compare(const void* pa, const void* pb) {
	const short *a = pa, *b = pb;
	if (*a > *b)
		return 1;
	else if (*a < *b)
		return -1;
	return 0;
}

int main() {
	int n;
	scanf("%d", &n);

	short list[100000];
	int i;
	for (i = 0; i < n; i++)
		scanf("%d", &list[i]);

	qsort(list, n, sizeof(short), compare);

	short last = -1;
	for (i = 0; i < n; i++) {
		if (list[i] != last) {
			last = list[i];
			printf("%d ", last);
		}
	}

	return 0;
}
