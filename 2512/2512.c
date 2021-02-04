#include <stdio.h>

// https://www.acmicpc.net/problem/2512 예산 <실버 3>

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

long long CalcMax(long long *billing, long long need, long long max, void* args) {
	long long i = 0, result = 0, area = *(long long*)args;

	for (i = 0; i < area; i++) {
		long long target = billing[i];

		if (target > max)
			result += max;
		else
			result += target;
	}

	return result <= need;
}

int main() {
	long long num;
	scanf("%lld", &num);
	long long billing[10000];
	long long max = 0;
	long long i;
	for (i = 0; i < num; i++) {
		scanf("%lld", billing + i);
		if (billing[i] >= max)
			max = billing[i];
	}

	long long need;
	scanf("%lld", &need);
	long long result = BinarySearch(billing, need, max, CalcMax, &num);
	printf("%lld\n", result);

	return 0;
}
