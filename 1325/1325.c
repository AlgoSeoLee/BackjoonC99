#include <stdio.h>
#include <stdlib.h>

typedef struct _Graph {
	int vertex;
	char** line;
} Graph;

Graph* GraphCreate(int vertex) {
	Graph* g = (Graph*)malloc(sizeof(Graph));
	g->vertex = vertex;
	g->line = (char**)malloc(sizeof(char*) * vertex);
	int i;
	for (i = 0; i < vertex; i++) {
		g->line[i] = (char*)calloc(vertex, sizeof(int));
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
	//g->line[from][to] = 1;
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

void EmptyIter(int vertex) {
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Graph* g = GraphCreate(n);

	while (m--) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--;
		b--;
		GraphInsertLine(g, a, b);
	}

	char* visited = (char*)calloc(n, sizeof(char));
	int i;
	for (i = 0; i < n; i++) {
		if (!visited[i]) {
			_DFS(g, EmptyIter, visited, i);
			printf("%d ", i+1);
		}
	}

	free(visited);
	GraphFree(g);

	printf("\n");
	return 0;
}
