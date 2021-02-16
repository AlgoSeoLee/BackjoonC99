#include <stdio.h>

int main() {
	int c;
	scanf("%d", &c);

	while (c--) {
		int startX = 0, startY = 0;
		scanf("%d %d", &startX, &startY);

		int length = 0;
		int invalid = 0;
		int x, y, i;
		for (i = 0; i < 3; i++) {
			scanf("%d %d", &x, &y);
			int diff = 0;
			if (startX != x)
				diff = startY > y ? startY - y : y - startY;
			else
				diff = startX > x ? startX - x : x - startX;

			if (length == 0)
				length = diff;
			else if (length != diff) {
				invalid = 1;
				break;
			}
		}

		printf("%d\n", invalid == 0 ? 1 : 0);
	}
}
