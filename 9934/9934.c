#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://www.acmicpc.net/problem/9934 완전 이진 트리 <실버 2>

int calcTreeLevel(int need) {
	int level = 0;
	do {
		level++;
	} while ((1 << level) * 2 - 1 <= need);

	level--;

	return level;
}

int CompleteBinaryTree(int* tree, int* building, int nums, int maxLv, int minLv, int pos, int lv) {
	while (lv > minLv && pos < nums) {
		int elem = building[pos];
		int cur = (1 << lv) - 1;
		while (tree[cur] != 0)
			cur++;

		tree[cur] = elem;

		if (maxLv != lv) {
			if (lv == 0) {
				int right = nums - pos - 1;
				maxLv = calcTreeLevel(right);
				maxLv++;
			}
				
			pos = CompleteBinaryTree(tree, building, nums, maxLv, lv, pos+1, maxLv);
		} else {
			pos++;
		}
		lv--;
	}

	return pos;
}

int main() {
	int maxLevel;
	scanf("%d", &maxLevel);
	maxLevel--;
	int treeSize = (1 << (maxLevel)) * 2 - 1;

	int* tree = (int*)calloc(treeSize, sizeof(int));

	getchar();

	int building[2049];
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

	CompleteBinaryTree(tree, building, elems, maxLevel, -1, 0, maxLevel);

	int i, lv = 0;
	for (i = 0; i < treeSize; i++) {
		if ((i + 1) >= (1 << lv)) {
			if (i != 0)
				printf("\n");
			lv++;
		}
		if (tree[i] != 0)
			printf("%d ", tree[i]);
	}
	printf("\n");

	free(tree);
	return 0;
}
