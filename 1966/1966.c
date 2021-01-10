#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/1966 프린터 큐 <실버 3> <발표>

typedef struct _Node {
	int value;
	int priority;
	void* next;
} Node;

typedef struct _Queue {
	Node* cur;
	Node* end;
} Queue;

void initQueue(Queue* queue) {
	queue->cur = NULL;
	queue->end = NULL;
}

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

void QueuePushValue(Queue* queue, int value, int priority) {
	Node* node = CreateNode(value, priority);
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

int CalcQueueMaximumPriority(Queue* queue) {
	Node* tmp = queue->cur;
	int maximum = -1;
	while (tmp != NULL) {
		if (tmp->priority > maximum)
			maximum = tmp->priority;
		tmp = tmp->next;
	}
	return maximum;
}

void QueueFree(Queue* queue) {
	while(queue->cur != NULL) {
		Node* tmp = QueuePullNode(queue);
		free(tmp);
	}
}

int main() {
	int c;
	scanf("%d", &c);

	while(c--) {
		int papers, target;
		scanf("%d %d", &papers, &target);

		Queue queue;
		initQueue(&queue);
		int i;
		for (i = 0; i < papers; i++) {
			int priority;
			scanf("%d", &priority);
			QueuePushValue(&queue, i, priority);
		}

		int maximum = CalcQueueMaximumPriority(&queue);
		int exit = 0;
		while(1) {
			Node* tmp = QueuePullNode(&queue);
			if (maximum == tmp->priority) {
				exit++;
				if (tmp->value == target) {
					printf("%d\n", exit);
					free(tmp);
					break;
				}
				free(tmp);
				maximum = CalcQueueMaximumPriority(&queue);
			} else
				QueuePushNode(&queue, tmp);
		}
		QueueFree(&queue);
	}
}
