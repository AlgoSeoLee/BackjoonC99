#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int calcTreeLevel(int need) {
	int level = 0;
	while (pow(2, level) < need) {
		level++;
	}

	return level;
}

int main() {
	int area, duck;
	scanf("%d %d", &area, &duck);

	int* tree = (int*)calloc(area, sizeof(int));

	while (duck--) {
		int need;
		scanf("%d", &need);
		need--;

		int level = calcTreeLevel(need);
		level--;

		int invalid = 0;
		int cur = need;
		do {
			if (level == 0)
				cur = 0;

			if (tree[cur] != 0) {
				invalid = tree[cur];
			}
			cur = cur - (pow(2, level) - 1);
			level--;
		} while (level >= 0);

		if (!invalid) {
			tree[need] = need + 1;
		}
		printf("%d\n", invalid);
	}

	free(tree);
	return 0;
}
