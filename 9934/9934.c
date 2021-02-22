#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calcTreeLevel(int need) {
	int level = 0;
	do {
		level++;
	} while ((1 << level) <= need);

	level--;

	return level;
}

int main() {
	int maxLevel;
	scanf("%d", &maxLevel);
	int treeSize = (1 << (maxLevel - 1)) * 2 - 1;

	int* tree = (int*)calloc(treeSize, sizeof(int));

	getchar();

	int building[2047];
	int elems = 0;

	char* buffer = NULL;
	size_t bufferSize = 0;
	size_t code = getline(&buffer, &bufferSize, stdin);
	char* token = strtok(buffer, " ");

	while (token != NULL) {
		int input = atoi(token);
		building[elems] = input;
		token = strtok(NULL, " ");
		elems++;
	}

	free(buffer);

	int level = maxLevel - 1, i;
	char div3 = 1, mid = 0;
	for (i = 0; level > 0; i++) {
		int cur = 1 << level;
		while (tree[cur - 1] != 0)
			cur++;
		tree[cur - 1] = building[i];

		if (div3 % 3 == 0) {
			div3 = 0;
			level -= 2;
		} else if (mid) {
			level += 1;
			mid = 0;
			div3++;
		} else {
			level -= 1;
			mid = 1;
			div3++;
		}
	}
	
	tree[0] = building[i];

	i++;
	level = maxLevel - 1;
	div3 = 1; mid = 0;
	for (; i < elems; i++) {
		int cur = 1 << level;
		while (tree[cur - 1] != 0)
			cur++;
		tree[cur - 1] = building[i];

		if (div3 % 3 == 0) {
			div3 = 0;
			level -= 2;
		} else if (mid) {
			level += 1;
			mid = 0;
			div3++;
		} else {
			level -= 1;
			mid = 1;
			div3++;
		}
	}

	int tmpLevel = 0, curLevel = 0;
	for (i = 0; i < treeSize; i++) {
		tmpLevel = calcTreeLevel(i+1);
		if (tmpLevel > curLevel) {
			printf("\n");
			curLevel = tmpLevel;
		}
		if (tree[i] != 0)
			printf("%d ", tree[i]);
	}
	printf("\n");

	free(tree);
	return 0;
}
