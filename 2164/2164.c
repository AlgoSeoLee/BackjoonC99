#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/2164 카드2 <실버 4>

typedef struct _Node {
	int value;
	void* next;
} Node;

typedef struct _Queue {
	Node* cur;
	Node* end;
	int length;
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
	queue->length = 0;
}

void QueuePushNode(Queue* queue, Node* node) {
	if (queue->cur == NULL) {
		queue->cur = node;
		queue->end = node;
		queue->length = 1;
	} else {
		queue->end->next = node;
		queue->end = node;
		queue->length++;
	}

	node->next = NULL;
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
		queue->length = 0;
	} else {
		queue->cur = (Node*)node->next;
		queue->length--;
	}

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

int QueueLength(Queue* queue) {
	return queue->length;
}

void QueueFree(Queue* queue) {
	NodeFree(queue->cur);
	queue->cur = NULL;
	queue->end = NULL;
}

int main() {
	Queue deck;
	QueueInit(&deck);

	int total;
	scanf("%d", &total);

	int i;
	for (i = 1; i <= total; i++) {
		QueuePushValue(&deck, i);
	}

	char drop = 1;
	while (QueueLength(&deck) != 1) {
		if (drop)
			QueuePullValue(&deck);
		else {
			Node* tmp = QueuePullNode(&deck);
			QueuePushNode(&deck, tmp);
		}

		drop = drop ? 0 : 1;
	}

	printf("%d\n", QueuePullValue(&deck));

	return 0;
}
