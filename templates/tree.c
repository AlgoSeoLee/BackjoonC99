#include <stdio.h>
#include <stdlib.h>

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

Tree* TreeInsertNode(Tree* tree, TreeDirection direction, int value) {
	Tree* newNode = CreateTree(value);
	switch (direction) {
		LEFT: tree->left = newNode; break;
		RIGHT: tree->right = newNode; break;
	}

	return newNode;
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
