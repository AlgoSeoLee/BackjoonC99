#include <stdlib.h>

typedef struct _Node {
	int value;
	void* next;
} Node;

typedef struct _Queue {
	Node* cur;
	Node* end;
} Queue;

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
	Node* node = NodeCreate(value);
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

int QueuePullValue(Queue* queue) {
	Node* node = QueuePullNode(queue);
	int tmp = node->value;
	free(node);

	return tmp;
}

int QueueEmpty(Queue* queue) {
	return queue->cur == NULL;
}

void QueueFree(Queue* queue) {
	NodeFree(queue->cur);
	queue->cur = NULL;
	queue->end = NULL;
}
