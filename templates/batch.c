#include <stdlib.h>

char** initBatch(int x, int y) {
	char** batch = (char**)malloc(sizeof(char*) * y);
	batch[0] = (char*)malloc(sizeof(char) * y * x);

	int i;
	for (i = 1; i < y; i++)
		batch[i] = batch[i - 1] + sizeof(char) * x * y;

	return batch;
}

char** freeBatch(char** batch) {
	free(batch[0]);
	free(batch);
}

// 디버깅 용
void printBatch(char** batch, int x, int y) {
	int i, j;
	for (i = 0; i < x; i++) {
		for (j = 0; j < y; j++) {
			printf("%d ", batch[i][j]);
		}
		printf("\n");
	}
}
