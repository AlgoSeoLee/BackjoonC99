#include <stdio.h>
#include <math.h>

#define NON_ZERO(a) a != 0 ? a : 1;

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

		int invalid = 0;

		int* a = points[0];
		int* b = points[1];
		int* c = points[2];

		float abTx = NON_ZERO(b[0] - a[0]);
		float bcTx = NON_ZERO(c[0] - b[0]);

		float abTy = NON_ZERO(b[1] - a[1]);
		float bcTy = NON_ZERO(c[1] - b[1]);

		int rSlopeAB = -(abTy / abTx);
		int SlopeBC = bcTx / bcTy;
		if (rSlopeAB != SlopeBC) {
			invalid = 1;
		} else {
			int length = 0;
			for (i = 1; i < 4; i++) {
				int* from = points[i - 1];
				int* to = points[i];

				int tx2 = pow(to[0] - from[0], 2);
				int ty2 = pow(to[1] - from[1], 2);

				int line = tx2 + ty2;
				if (from[0] == from[0])
					line = ty2;
				else if (from[1] == from[1])
					line = tx2;
				else
					line = tx2 + ty2;

				if (length == 0)
					length = line;
				else if (length != line) {
					invalid = 1;
					break;
				}
			}
		}

		printf("%d\n", invalid == 0 ? 1 : 0);
	}

	return 0;
}
