#include <stdlib.h>

typedef struct _Node {
	int value;
	void* next;
} Node;

typedef struct _Queue {
	Node* start;
	Node* end;
} Queue;

void initNode(Node* node, int value) {
	node->value = value;
	node->next = NULL;
}

Node* CreateNode(int value) {
	Node* node = (Node*)malloc(sizeof(Node));
	initNode(node, value);
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

Node* insertNodeByValue(Node* list, int value) {
	Node* next = CreateNode(value);
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

void QueueInit(Queue* queue) {
	queue->cur = NULL;
	queue->end = NULL;
}

void QueuePushNode(Queue* queue, Node* node) {
	if (queue->cur == NULL) {
		queue->cur = node;
		queue->end = node;
		return;
	}

	node->next = NULL;
	queue->end->next = node;
	queue->end = node;
}

void QueuePushValue(Queue* queue, int value) {
	Node* node = CreateNode(value);
	QueuePushNode(queue, node);
}

Node* QueuePullNode(Queue* queue) {
	Node* node = queue->cur;
	if (queue->cur == queue->end) {
		queue->cur = NULL;
		queue->end = NULL;
	} else
		queue->cur = (Node*)node->next;
	return node;
}

void QueueFree(Queue* queue) {
	freeNode(queue->cur);
	queue->cur = NULL;
	queue->end = NULL;
}

