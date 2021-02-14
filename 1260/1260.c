#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/1260 DFS와 BFS <실버 2> 

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
	int** line;
} Graph;

Graph* GraphCreate(int vertex) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vertex = vertex;
	g->line = (int**)malloc(sizeof(int*) * vertex);
	int i;
	for (i = 0; i < vertex; i++) {
		g->line[i] = (int*)calloc(vertex, sizeof(int));
	}

	return g;
}

void GraphFree(Graph* g) {
	int i;
	for (i = 0; i < g->vertex; i++) {
		free(g->line[i]);
	}
	free(g->line);
	free(g);
}

void GraphInsertLine(Graph* g, int from, int to) {
	g->line[from][to] = 1;
	g->line[to][from] = 1;
}

typedef void (*GraphIterator)(int vertex);

void _DFS(Graph* g, GraphIterator func, char *visited, int target) {
	func(target);
	visited[target] = 1;

	int i;
	for (i = 0 ; i < g->vertex; i++) {
		if (g->line[target][i] && !visited[i])
			_DFS(g, func, visited, i);
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

		int i;
		for (i = 0; i < g->vertex; i++) {
			if (g->line[cur][i] && !visited[i]) {
				visited[i] = 1;
				QueuePushValue(&queue, i);
				func(i);
			}
		}
	}

	QueueFree(&queue);
	free(visited);
}

void PrintVertex(int vertex) {
	printf("%d ", vertex + 1);
}

int main() {
	int vertex, line, start;
	scanf("%d %d %d", &vertex, &line, &start);
	Graph* g = GraphCreate(vertex);
	start--;

	int i;
	for (i = 0; i < line; i++) {
		int from, to;
		scanf("%d %d", &from, &to);
		from--;
		to--;
		GraphInsertLine(g, from, to);
	}

	GraphDFS(g, PrintVertex, start);
	printf("\n");

	GraphBFS(g, PrintVertex, start);
	printf("\n");

	GraphFree(g);

	return 0;
}
