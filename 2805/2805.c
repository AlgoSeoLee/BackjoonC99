#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/2805 나무 자르기 <실버 3>

typedef long long (*BinarySearchComparator)(long long* arr, long long target, long long mid, void* args);
long long BinarySearch(long long* arr, long long target, long long length, BinarySearchComparator func, void* args) {
	long long start = 1;
	long long end = length;

	long long result = 0;
	long long comp = 0;
	while (start <= end) {
		long long mid = (start + end) / 2;
		long long current = func(arr, target, mid, args);

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

long long CalcHeight(long long *trees, long long need, long long height, void* args) {
	long long i = 0;
	long long result = 0;
	long long num = *(long long*)args;

	for (i = 0; i < num; i++) {
		long long target = trees[i];

		if (target > height)
			result += target - height;
	}

	return result >= need;
}

long long main() {
	long long num, need;
	scanf("%lld %lld", &num, &need);
	long long* trees = (long long*)calloc(num, sizeof(long long));
	long long max = 0;
	long long i;
	for (i = 0; i < num; i++) {
		scanf("%lld", trees + i);
		if (trees[i] >= max)
			max = trees[i];
	}

	long long result = BinarySearch(trees, need, max, CalcHeight, &num);
	printf("%lld\n", result);

	free(trees);

	return 0;
}
