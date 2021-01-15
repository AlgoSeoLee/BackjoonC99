#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/4256 4256 트리 <골드 5>

typedef struct _Tree {
	int value;
	void* left;
	void* right;
} Tree;

typedef enum _TreeDirection {
	LEFT,
	RIGHT
} TreeDirection;

Tree* CreateTree(int value) {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;

	return tree;
}

typedef void (*TreeIterFunc) (Tree*);

void TreePostOrderIterate(Tree* tree, TreeIterFunc func) {
	if (tree->left != NULL)
		TreePostOrderIterate(tree->left, func);
	if (tree->right != NULL)
		TreePostOrderIterate(tree->right, func);

	func(tree);
}

void _FreeTree(Tree* tree) {
	free(tree);
}

void FreeTree(Tree* tree) {
	TreePostOrderIterate(tree, _FreeTree);
}

void _PrintTree(Tree* tree) {
	printf("%d ", tree->value);
}

void PrintTree(Tree* tree) {
	TreePostOrderIterate(tree, _PrintTree);
	printf("\n");
}

int makeTree(Tree** tree, int length, int* pre, int* in, int cur, int start, int end) {
	int root = pre[cur];
	if (cur == length)
		return cur;
	*tree = CreateTree(root);
	cur++;

	if (start == end) {
		return cur;
	}

	int mid = start;
	while (in[mid] != root)
		mid++;

	if (mid != start)
		cur = makeTree(&((*tree)->left), length, pre, in, cur, start, mid-1);

	if (mid != end)
		cur = makeTree(&((*tree)->right), length, pre, in, cur, mid+1, end);

	return cur;
}

int main() {
	int cases;
	scanf("%d", &cases);

	while(cases--) {
		int len, *pre, *in;
		scanf("%d", &len);
		pre = (int*)malloc(sizeof(int) * len);
		in = (int*)malloc(sizeof(int) * len);

		int i;
		for (i = 0; i < len; i++) {
			scanf("%d", &pre[i]);
		}
		for (i = 0; i < len; i++) {
			scanf("%d", &in[i]);
		}

		Tree *result = NULL;
		makeTree(&result, len, pre, in, 0, 0, len);
		PrintTree(result);
		FreeTree(result);
		free(pre);
		free(in);

	}
	return 0;
}
