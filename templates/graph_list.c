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

typedef struct _Graph {
	int vertex;
	Queue* line;
} Graph;

Graph* GraphCreate(int vertex) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vertex = vertex;
	g->line = (Queue*)malloc(sizeof(Queue) * vertex);
	int i;
	for (i = 0; i < vertex; i++)
		QueueInit(&g->line[i]);

	return g;
}

void GraphFree(Graph* g) {
	int i;
	for (i = 0; i < g->vertex; i++)
		QueueFree(&g->line[i]);
	free(g->line);
	free(g);
}

void GraphInsertLine(Graph* g, int from, int to) {
	QueuePushValue(&g->line[from], to);
	QueuePushValue(&g->line[to], from);
}

typedef void (*GraphIterator)(int vertex);

void _DFS(Graph* g, GraphIterator func, char *visited, int target) {
	func(target);
	visited[target] = 1;

	Node* tmp = (g->line[target]).cur;
	while (tmp != NULL) {
		int now = tmp->value;
		if (!visited[now])
			_DFS(g, func, visited, now);
		tmp = tmp->next;
	}
}

void GraphDFS(Graph* g, GraphIterator func, int start) {
	char* visited = (char*)calloc(g->vertex, sizeof(char));

	_DFS(g, func, visited, start);
	free(visited);
}

void GraphBFS(Graph* g, GraphIterator func, int start) {
	Queue queue;
	QueueInit(&queue);
	QueuePushValue(&queue, start);
	char* visited = (char*)calloc(g->vertex, sizeof(char));
	visited[start] = 1;
	func(start);

	while(!QueueEmpty(&queue)) {
		int cur = QueuePullValue(&queue);

		Node* tmp = (g->line[cur]).cur;
		while (tmp != NULL) {
			int now = tmp->value;
			if (!visited[now]) {
				visited[now] = 1;
				QueuePushValue(&queue, now);
				func(now);
			}
		}
	}

	QueueFree(&queue);
	free(visited);
}
