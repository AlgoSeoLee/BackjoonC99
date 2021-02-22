#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/20364 부동산 다툼 <실버 2> 

int calcTreeLevel(int need) {
	int level = 0;
	do {
		level++;
	} while ((1 << level) <= need);

	level--;

	return level;
}

int main() {
	int area, duck;
	scanf("%d %d", &area, &duck);

	int* tree = (int*)calloc(area, sizeof(int));

	while (duck--) {
		int need;
		scanf("%d", &need);

		int level = calcTreeLevel(need);

		int invalid = 0;
		int cur = need;
		do {
			if (tree[cur - 1] != 0) {
				invalid = cur;
			}
			cur = (1 << (level - 1)) + (cur - (1 << level)) / 2;
			level--;
		} while (level >= 0);

		if (!invalid) {
			tree[need - 1] = 1;
		}
		printf("%d\n", invalid);
	}

	free(tree);
	return 0;
}
