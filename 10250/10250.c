#include <stdio.h>

int main() {
	int c, h, v, i, f, r;
	const char* format = "%d%0.2d\n";

	scanf("%d", &c);

	for(i = 0; i < c; i++) {
		scanf("%d %d %d", &h, &v, &v);
		f = v % h;
		r = v / h;
		if (f == 0)
			printf(format, h, r);
		else
			printf(format, f, r + 1);
	}
}
