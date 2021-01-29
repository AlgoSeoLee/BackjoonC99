#include <stdio.h>

// https://www.acmicpc.net/problem/1292 쉽게 푸는 문제 <실버 4>

int main() {
	int start, end;
	scanf("%d %d", &start, &end);

	int i = 1, count = 0, sum = 0, keep = 1;
	while (keep) {
		int j;
		for (j = 0; j < i; j++) {
			count++;
			if (count >= start) {
				if (count > end) {
					keep = 0;
					break;
				}

				sum += i;
			}
		}

		i++;
	}

	printf("%d\n", sum);

	return 0;
}
