#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/5639 이진 검색 트리 <실버 1>

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

void TreePostOrderIterate(Tree* tree, TreeIterFunc func) {
	if (tree->left != NULL)
		TreePostOrderIterate(tree->left, func);
	if (tree->right != NULL)
		TreePostOrderIterate(tree->right, func);

	func(tree);
}

void _PrintTree(Tree* tree) {
	printf("%d\n", tree->value);
}

void PrintTree(Tree* tree) {
	TreePostOrderIterate(tree, _PrintTree);
}

void _FreeTree(Tree* tree) {
	free(tree);
}

void FreeTree(Tree* tree) {
	TreePostOrderIterate(tree, _FreeTree);
}


int getInteger() {
	char* buffer = NULL;
	int length = NULL;
	int size = getline(&buffer, &length, stdin);
	if (size < 0) {
		return -1;
	}

	return atoi(buffer);
}

int main() {
	int value = getInteger();
	Tree* root = CreateTree(value);
	
	value = getInteger();
	while (value >= 0) {
		Tree* cur = root;
		while (1) {
			Tree** next;
			if (cur->value > value)
				next = &cur->left;
			else 
				next = &cur->right;

			if (*next == NULL) {
				*next = CreateTree(value);
				break;
			}

			cur = *next;
		}

		value = getInteger();
	}

	PrintTree(root);
	FreeTree(root);
}

