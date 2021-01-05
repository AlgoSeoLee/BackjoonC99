#include <stdio.h>

void initSeive(int *seive) {
	int i, j, addr;
	for (i = 0; i < 1000; i++)
		seive[i] = 0;

	for (i = 2; i <= 1000; i++) {
		addr = i - 2;
		if (seive[addr] == 0) {
			for (j = addr + i; j < 1000; j += i)
				seive[j] = i;
		}
	}
}

int searchSeive(int *seive, int target) {
	if (target < 2)
		return -1;
	return seive[target - 2];
}

int main() {
	int seive[999];
	initSeive(seive);

	int c, i, target, result = 0;
	scanf("%d", &c);

	for (i = 0; i < c; i++) {
		scanf("%d", &target);
		if (searchSeive(seive, target) == 0)
			result++;
	}

	printf("%d", result);

	return 0;
}
