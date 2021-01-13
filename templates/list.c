#include <stdlib.h>

typedef struct _Node {
	int value;
	int priority;
	void* next;
} Node;

void initNode(Node* node, int value, int priority) {
	node->value = value;
	node->priority = priority;
	node->next = NULL;
}

Node* CreateNode(int value, int priority) {
	Node* node = (Node*)malloc(sizeof(Node));
	initNode(node, value, priority);
	return node;
}

void insertNode(Node* list, Node* next) {
	if (list == NULL) {
		list = next;
		return;
	}

	Node* last = list;
	while (last->next != NULL)
		last = last->next;

	last->next = node;
}

Node* insertNodeByValue(Node* list, int value, int priority) {
	Node* next = CreateNode(value, priority);
	insertNode(list, node);
	return next;
}

void freeNode(Node* list) {
	if (list == NULL) {
		return;
	}

	Node* tmp = list;
	while (tmp != NULL) {
		Node* next = tmp->next;
		free(tmp);
		tmp = next;
	}
}
