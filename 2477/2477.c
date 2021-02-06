#include <stdio.h>

// https://www.acmicpc.net/problem/2477 참외밭 <실버 5>

typedef enum _Direction {
	INIT = 0,
	RIGHT = 1,
	LEFT,
	UP,
	DOWN
} Direction;

int main() {
	int k;
	scanf("%d", &k);

	int border[6];
	Direction direction[6];
	int i;
	for (i = 0; i < 6; i++) {
		int dir;
		int len;
		scanf("%d %d", &dir, &len);

		border[i] = len;
		direction[i] = dir;
	}

	int maxX = 0, maxY = 0, privX = 0, privY = 0;
	Direction privXD = INIT, privYD = INIT;
	int blank = 0;
	for (i = 0; i < 6; i++) {
		int target = border[i];
		Direction dir = direction[i];

		if (!blank) {
			switch (dir) {
				case RIGHT:
				blank = privYD != UP ? privY * target : blank; break;
				case LEFT:
				blank = privYD != DOWN ? privY * target : blank; break;
				case UP:
				blank = privXD != LEFT ? privX * target : blank; break;
				case DOWN:
				blank = privXD != RIGHT ? privX * target : blank; break;
			}
		}

		switch (dir) {
			case RIGHT:
			case LEFT:
			if (target > maxX)
				maxX = target;

			if (!blank) {
				privX = target;
				privXD = dir;
			}
			break;
			case UP:
			case DOWN:
			if (target > maxY)
				maxY = target;

			if (!blank) {
				privY = target;
				privYD = dir;
			}
			break;
		}
	}

	if (!blank)
		blank = border[0] * border[5];

	printf("%d\n", k * (maxX * maxY - blank));

	return 0;
}
