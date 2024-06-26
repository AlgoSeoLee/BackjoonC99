#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// https://www.acmicpc.net/problem/2447 별 찍기 - 10 <실버 1>

const char FILLED_LINE[3] = {1, 1, 1};
const char SECOND_LINE[3] = {1, 0, 1};

const char EMPTY_LINE[3] = {0, 0, 0};

void emptySpace(char** batch, int size, int x, int y) {
	if (size == 3) {
		int i;
		for (i = 0; i < 3; i++)
			memcpy(&batch[y + i][x], EMPTY_LINE, 3);
		return;
	}

	int sizeDiv3 = size / 3;
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			emptySpace(
				batch,
				sizeDiv3,
				x + i * sizeDiv3,
				y + j * sizeDiv3);
		}
	}
}

void makeStar(char** batch, int size, int x, int y) {
	if (size == 3) {
		memcpy(&batch[y][x], FILLED_LINE, 3);
		memcpy(&batch[y + 1][x], SECOND_LINE, 3);
		memcpy(&batch[y + 2][x], FILLED_LINE, 3);
		return;
	}

	int sizeDiv3 = size / 3;
	int i, j;
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (i == 1 && j == 1) {
				emptySpace(
					batch,
					sizeDiv3,
					x + i * sizeDiv3,
					y + j * sizeDiv3);
				continue;
			}
			makeStar(
				batch,
				sizeDiv3,
				x + i * sizeDiv3,
				y + j * sizeDiv3);
		}
	}
}

void printStarBatch(char** batch, int sizeDiv3) {
	int x, y, line;
	for (x = 0; x < sizeDiv3; x++) {
		for (line = 0; line < 3; line++) {
			for (y = 0; y < sizeDiv3; y++) {
				if (batch[y][x] == 0)
					printf("   ");
				else if (line == 0 || line == 2)
					printf("***");
				else
					printf("* *");
			}
			printf("\n");
		}
	}
}

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

int main() {
	int lines;
	scanf("%d", &lines);

	lines = lines / 3;
	char** batch = initBatch(lines, lines);

	if (lines == 1) {
		batch[0][0] = 1;
	} else {
		makeStar(batch, lines, 0, 0);
	}

	printStarBatch(batch, lines);

	freeBatch(batch);

	return 0;
}
