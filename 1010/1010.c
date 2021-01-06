#include <stdio.h>

int simulateBridge(int left, int right) {
	if (left == right)
		return 1;
	else if (left == 1)
		return right;

	int i, sum = 0;
	const int rest = right - left;

	for (i = 1; i <= rest + 1; i++) {
		sum += simulateBridge(left - 1, right - i);
	}

	return sum;
}

int main() {
	int c;
	scanf("%d", &c);

	int i;
	for (i = 0; i < c; i++) {
		int left, right;
		scanf("%d %d", &left, &right);
		printf("%d\n", simulateBridge(left, right));
	}
}
