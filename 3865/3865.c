#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Tree {
	char* name;
	void* sibiling;
	void* child;
} Tree;

void InitNode(Tree* tree, char* name) {
	size_t name_length = strlen(name);
	tree->name = (char*)malloc(name_length * sizeof(char));
	strcpy(tree->name, name);
	tree->sibiling = NULL;
	tree->child = NULL;
}

Tree* CreateNode(char* name) {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	InitNode(tree, name);
	return tree;
}

typedef enum _TreeIterState {
	KEEP = 0,
	RETURN,
} TreeIterState;

typedef struct _TreeIterInfo {
	void* arg;
	Tree* top;
	Tree* prev;
} TreeIterInfo;

typedef TreeIterState (*TreeIterFunc)(Tree*, TreeIterInfo*, int);

typedef enum _IsLeaf {
	LEAF,
	NON_LEAF
} IsLeaf;

Tree* IterateTree(Tree* tree, TreeIterFunc work, TreeIterInfo info, TreeIterState* state) {
	Tree* cur = tree->child;
	TreeIterInfo newInfo;
	newInfo.arg = info.arg;
	newInfo.top = tree;
	newInfo.prev = NULL;
	int is_leaf = LEAF;
	while (cur != NULL) {
		is_leaf = NON_LEAF;
		Tree *result = IterateTree(cur, work, newInfo, state);
		if (state != NULL) {
			if (*state == RETURN)
				return result;
		}
		newInfo.prev = cur;
		cur = cur->sibiling;
	}

	if (state != NULL)
		*state = work(tree, &info, is_leaf);
	else
		work(tree, &info, is_leaf);
	return tree;
}

TreeIterState _FindByNameTree(Tree* tree, TreeIterInfo* info, int is_leaf) {
	void* arg = info->arg;
	if (strcmp((char*)arg, tree->name) == 0)
		return RETURN;

	return KEEP;
}

Tree* FindByNameTree(Tree* tree, char* name) {
	TreeIterState state;
	TreeIterInfo info;
	info.arg = name;
	Tree* result = IterateTree(tree, _FindByNameTree, info, &state);
	if (state == KEEP)
		return NULL;

	return result;
}

TreeIterState _DeleteByNameTree(Tree* tree, TreeIterInfo* info, int is_leaf) {
	void* arg = info->arg;
	Tree* prev = info->prev;
	if (strcmp((char*)arg, tree->name) == 0) {
		if (prev != NULL) {
			prev->sibiling = tree->sibiling;
		} else {
			info->top->child = tree->sibiling;
		}
		return RETURN;
	}

	return KEEP;
}

Tree* DeleteByNameTree(Tree* tree, char* name) {
	TreeIterState state;
	TreeIterInfo info;
	info.top = tree;
	info.arg = name;
	Tree* result = IterateTree(tree, _DeleteByNameTree, info, &state);
	if (state == KEEP)
		return NULL;

	return result;
}

TreeIterState _CountLeafNodeTree(Tree* tree, TreeIterInfo* info, int is_leaf) {
	void* arg = info->arg;
	if (is_leaf == LEAF) {
		int* leaves = arg;
		(*leaves)++;
	}

	return KEEP;
}

int CountLeafNodeTree(Tree* tree) {
	int leaves = 0;
	TreeIterInfo info;
	info.arg = &leaves;
	IterateTree(tree, _CountLeafNodeTree, info, NULL);
	return leaves;
}

Tree* InsertNodeTree(Tree* tree, char* name) {
	Tree* result = NULL;
	Tree* child = tree->child;

	if (child == NULL) {
		child = CreateNode(name);
		result = child;
		tree->child = child;
	} else {
		Tree* last = child;
		while (last->sibiling != NULL)
			last = last->sibiling;
		last->sibiling = CreateNode(name);
		result = last->sibiling;
	}

	return result;
}

TreeIterState _FreeTree(Tree *tree, TreeIterInfo* info, int is_leaf) {
	free(tree->name);
	free(tree);
	return KEEP;
}

void FreeTree(Tree *tree) {
	TreeIterInfo info;
	IterateTree(tree, _FreeTree, info, NULL);
}

TreeIterState _PrintTree(Tree *tree, TreeIterInfo* info, int is_leaf) {
	printf("%s ", tree->name);
	return KEEP;
}

void PrintTree(Tree *tree) {
	TreeIterInfo info;
	IterateTree(tree, _PrintTree, info, NULL);
	printf("\n");
}

int main() {
	while (1) {
		int c;
		Tree *tree = CreateNode("ROOT");
		Tree *academy = NULL;

		scanf("%d", &c);
		if (c == 0) {
			break;
		}

		int i;
		char line[161];
		for(i = 0; i < c; i++) {
			scanf("%s", line);
			char *word = strtok(line, ":,.");
			if (i == 0) {
				academy = InsertNodeTree(tree, word);
				word = strtok(NULL, ":,.");
				while (word != NULL) {
					InsertNodeTree(academy, word);
					word = strtok(NULL, ":,.");
				}
			} else {
				Tree* subAcademy = FindByNameTree(academy, word);
				int is_main = 1;
				if (subAcademy == NULL) {
					subAcademy = InsertNodeTree(tree, word);
					is_main = 0;
				}

				word = strtok(NULL, ":,.");
				while (word != NULL) {
					Tree *duplicate =
						is_main ? DeleteByNameTree(tree,word):FindByNameTree(tree, word);
					if (duplicate == NULL) {
						InsertNodeTree(subAcademy, word);
					} else if (is_main) {
						Tree* node = InsertNodeTree(subAcademy, word);
						node->child = duplicate->child;
						free(duplicate);
					}
					word = strtok(NULL, ":,.");
				}
			}
		}

		PrintTree(academy);
		printf("%d\n", CountLeafNodeTree(academy));
		FreeTree(tree);
	}

	return 0;
}
