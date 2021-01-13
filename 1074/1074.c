#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/1074 Z <실버 1>

int trackZ(int start, int x, int y, int size, int tx, int ty) {
	if (size == 2) {
		int i;
		for (i = 0; i < 2; i++) {
			int sum = i + start;
			if (y == ty && x+i == tx)
				return sum;
			else if (y+1 == ty && x+i == tx)
				return sum + 2;
		}
		return -1;
	}

	int sizeDiv2 = size / 2;
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 2; j++) {
			int diffX = sizeDiv2 * j;
			int diffXend = sizeDiv2 * (j + 1);
			int diffY = sizeDiv2 * i;
			int diffYend = sizeDiv2 * (i + 1);
			int diff = (i * 2 + j) * sizeDiv2 * sizeDiv2;

			int result = -1;
			if (tx >= x + diffX && tx < x + diffXend &&
				ty >= y + diffY && ty < y + diffYend)
				result = trackZ(start + diff, x + diffX, y + diffY, sizeDiv2, tx, ty);

			if (result != -1) {
				return result;
			}
		}
	}

	return -1;
}

int main() {
	int N, size = 1;
	scanf("%d", &N);
	while (N--)
		size *= 2;

	int r, c;
	scanf("%d %d", &r, &c);
	printf("%d\n", trackZ(0, 0, 0, size, c, r));

	return 0;
}
