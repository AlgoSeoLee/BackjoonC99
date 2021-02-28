#include <stdio.h>
#include <math.h>
#include <limits.h>

// https://www.acmicpc.net/problem/1485 정사각형 <실버 4>

int main() {
	int c;
	scanf("%d", &c);

	int points[4][2];

	while (c--) {
		int i;
		for (i = 0; i < 4; i++) {
			int* p = points[i];
			scanf("%d %d", p, p+1);
		}

		int invalid = 0, min = INT_MAX;
		char origin[2], originI = 0;
		for (i = 0; i < 4; i++) {
			int j;
			char far = 0;
			for (j = 0; j < 4; j++) {
				if (i == j)
					continue;
				int* from = points[i];
				int* to = points[j];

				int tx2 = pow(to[0] - from[0], 2);
				int ty2 = pow(to[1] - from[1], 2);

				int line = tx2 + ty2;

				if (line < min) {
					min = line;
					if (i == 0) {
						origin[0] = j;
						if (originI == 0)
							originI++;
						else
							far++;
					}
				} else if (line > min)
					far++;
				else {
					if (i == 0)
						origin[originI] = j;
				}
			}

			if (far != 1) {
				invalid = 1;
				break;
			}
		}

		if (!invalid) {
			int* a = points[origin[0]];
			int* b = points[0];
			int* c = points[origin[1]];

			float abTx = b[0] - a[0];
			float bcTx = c[0] - b[0];

			float abTy = b[1] - a[1];
			float bcTy = c[1] - b[1];

			int rSlopeAB = -(abTy / abTx);
			int SlopeBC = bcTx / bcTy;
			if (rSlopeAB != SlopeBC)
				invalid = 1;
		}

		printf("%d\n", invalid == 0 ? 1 : 0);
	}

	return 0;
}
