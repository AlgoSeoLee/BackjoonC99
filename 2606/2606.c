#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/2606 바이러스 <실버 3>

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

static int WORM_COUNT;
void CalcInfectWorm(int num) {
	WORM_COUNT++;
}

int main() {
	int vertex, line;
	scanf("%d %d", &vertex, &line);
	Graph* g = GraphCreate(vertex);

	int i;
	for (i = 0; i < line; i++) {
		int from, to;
		scanf("%d %d", &from, &to);
		from--;
		to--;
		GraphInsertLine(g, from, to);
	}

	GraphDFS(g, CalcInfectWorm, 0);
	printf("%d\n", WORM_COUNT - 1);

	GraphFree(g);

	return 0;
}
