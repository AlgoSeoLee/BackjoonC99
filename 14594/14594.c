#include <stdio.h>

// https://www.acmicpc.net/problem/14594 <실버 3> 동방 프로젝트 (small)

int main() {
	int N, com, offices[100];
	scanf("%d", &N);
	scanf("%d", &com);
	int i;
	for (i = 0; i < N; i++) {
		offices[i] = 1;
	}

	while (com--) {
		int x, y;
		scanf("%d %d", &x, &y);
		y--;

		if ((!offices[x - 1]) && x != 1) {
			offices[x] = 0;
		}

		for (; x <= y; x++) {
			offices[x] = 0;
		}
	}

	int sum = 0;
	for (i = 0; i < N; i++) {
		if (offices[i]) {
			sum++;
		}
	}

	printf("%d\n", sum);

	return 0;
}
