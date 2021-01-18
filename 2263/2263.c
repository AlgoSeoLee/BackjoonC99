#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/2263 트리의 순회 <골드 3>
typedef struct _Tree {
	int value;
	void* left;
	void* right;
} Tree;

Tree* CreateTree(int value) {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->value = value;
	tree->left = NULL;
	tree->right = NULL;

	return tree;
}

typedef void (*TreeIterFunc) (Tree*);

void TreePreOrderIterate(Tree* tree, TreeIterFunc func) {
	func(tree);

	if (tree->left != NULL)
		TreePreOrderIterate(tree->left, func);
	if (tree->right != NULL)
		TreePreOrderIterate(tree->right, func);
}

void TreePostOrderIterate(Tree* tree, TreeIterFunc func) {
	if (tree->left != NULL)
		TreePostOrderIterate(tree->left, func);
	if (tree->right != NULL)
		TreePostOrderIterate(tree->right, func);

	func(tree);
}

void _PrintTree(Tree* tree) {
	printf("%d ", tree->value);
}

void PrintTree(Tree* tree) {
	TreePreOrderIterate(tree, _PrintTree);
	printf("\n");
}

void _FreeTree(Tree* tree) {
	free(tree);
}

void FreeTree(Tree* tree) {
	TreePostOrderIterate(tree, _FreeTree);
}

int makeTree(Tree** tree, int length, int* post, int* in, int cur, int start, int end) {
	int root = post[cur];
	if (cur < 0 || length == start)
		return cur;
	*tree = CreateTree(root);
	cur--;

	if (start == end) {
		return cur;
	}

	int mid = start;
	while (in[mid] != root)
		mid++;

	if (mid != end)
		cur = makeTree(&((*tree)->right), length, post, in, cur, mid+1, end);

	if (mid != start)
		cur = makeTree(&((*tree)->left), length, post, in, cur, start, mid-1);


	return cur;
}

int main() {
	int len, *post, *in;
	scanf("%d", &len);
	post = (int*)malloc(sizeof(int) * len);
	in = (int*)malloc(sizeof(int) * len);

	int i;
	for (i = 0; i < len; i++) {
		scanf("%d", &in[i]);
	}
	for (i = 0; i < len; i++) {
		scanf("%d", &post[i]);
	}

	Tree *result = NULL;
	makeTree(&result, len, post, in, len - 1, 0, len);
	PrintTree(result);
	FreeTree(result);
	free(post);
	free(in);

	return 0;
}
