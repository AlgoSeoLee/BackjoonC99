#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Node {
	void* data;
	void* next;
} Node;

typedef struct _Tree {
	char* name;
	Node* child;
} Tree;

typedef enum _TreeIterState {
	KEEP = 0,
	RETURN,
} TreeIterState;

typedef TreeIterState (*TreeIterFunc)(Tree*, void*, int);

void InitTree(Tree* tree, char* name) {
	size_t name_length = strlen(name);
	tree->name = (char*)calloc(name_length, sizeof(char));
	strcpy(tree->name, name);
	tree->child = NULL;
}

Node* CreateNode(char* name) {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	InitTree(tree, name);
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = tree;
	node->next = NULL;

	return node;
}

typedef enum _IsLeaf {
	LEAF,
	NON_LEAF
} IsLeaf;

Tree* IterateTree(Tree* tree, TreeIterFunc work, void* arg, TreeIterState* state) {
	Node* cur = tree->child;
	int is_leaf = LEAF;
	while (cur != NULL) {
		is_leaf = NON_LEAF;
		Tree *next = cur->data;
		Tree *result = IterateTree(next, work, arg, state);
		if (state != NULL) {
			if (*state == RETURN)
				return result;
		}
		cur = cur->next;
	}

	if (state != NULL)
		*state = work(tree, arg, is_leaf);
	else
		work(tree, arg, is_leaf);
	return tree;
}

TreeIterState _FindByNameTree(Tree* tree, void* arg, int is_leaf) {
	if (strcmp((char*)arg, tree->name) == 0)
		return RETURN;

	return KEEP;
}

Tree* FindByNameTree(Tree* tree, char* name) {
	TreeIterState state;
	Tree* result = IterateTree(tree, _FindByNameTree, name, &state);
	if (state == KEEP)
		return NULL;

	return result;
}

TreeIterState _CountLeafNodeTree(Tree* tree, void* arg, int is_leaf) {
	if (is_leaf == LEAF) {
		int* leaves = arg;
		(*leaves)++;
	}

	return KEEP;
}

int CountLeafNodeTree(Tree* tree) {
	int leaves = 0;
	IterateTree(tree, _CountLeafNodeTree, &leaves, NULL);
	return leaves;
}

Tree* InsertNodeTree(Tree* tree, char* name) {
	Tree* result = NULL;
	Node* child = tree->child;

	if (child == NULL) {
		child = CreateNode(name);
		result = (Tree*)child->data;
	} else {
		child->next = CreateNode(name);
		result = (Tree*)((Node*)child->next)->data;
	}

	tree->child = child;
	return result;
}

TreeIterState _FreeTree(Tree *tree, void* args, int is_leaf) {
	free(tree->name);
	free(tree->child);
}

void FreeTree(Tree *tree) {
	IterateTree(tree, _FreeTree, NULL, NULL);
	free(tree);
}

int main() {
	while (1) {
		int c;
		Tree *tree = (Tree*)malloc(sizeof(Tree));
		InitTree(tree, "ROOT");

		scanf("%d", &c);
		if (c == 0) {
			break;
		}

		Tree* academy;

		int i;
		char line[160];
		for(i = 0; i < c; i++) {
			scanf("%s", line);
			char *word = strtok(line, ":,.");
			if (i == 0) {
				InsertNodeTree(tree, word);
				academy = tree->child->data;
				word = strtok(NULL, ":,.");
				while (word != NULL) {
					InsertNodeTree(academy, word);
					word = strtok(NULL, ":,.");
				}
			} else {
				Tree* subAcademy = FindByNameTree(academy, word);
				if (subAcademy != NULL) {
					word = strtok(NULL, ":,.");
					while (word != NULL) {
						Tree *duplicate = FindByNameTree(academy, word);
						if (duplicate == NULL) {
							InsertNodeTree(subAcademy, word);
						}
						word = strtok(NULL, ":,.");
					}
				}
			}
		}

		printf("%d\n", CountLeafNodeTree(academy));
		FreeTree(academy);
	}

	return 0;
}
