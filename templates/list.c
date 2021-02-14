#include <stdlib.h>

typedef struct _Node {
	int value;
	void* next;
} Node;

void NodeInit(Node* node, int value) {
	node->value = value;
	node->next = NULL;
}

Node* NodeCreate(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	NodeInit(node, value);
	return node;
}

void NodeInsert(Node* list, Node* next) {
	if (list == NULL) {
		list = next;
		return;
	}

	Node* last = list;
	while (last->next != NULL)
		last = last->next;

	last->next = next;
}

Node* NodeInsertByValue(Node* list, int value) {
	Node* next = NodeCreate(value);
	NodeInsert(list, next);
	return next;
}

void NodeFree(Node* list) {
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
