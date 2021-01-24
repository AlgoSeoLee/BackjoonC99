#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/15787 기차가 어둠을 헤치고 은하수를 <실버 1>

#define FULL_CAR 0b11111111111111111111

int main() {
	int* train = NULL;
	int car, com;
	scanf("%d %d", &car, &com);
	train = (int*)calloc(car, sizeof(int));

	while (com--) {
		int command, where;
		scanf("%d %d", &command, &where);
		where--;

		int seat, target = 1;
		switch (command) {
			case 1:
			case 2:
			scanf("%d", &seat);
			target = target << (seat - 1);
			break;
			default:
			break;
		}

		switch (command) {
			case 1:
			train[where] = train[where] | target;
			break;
			case 2:
			train[where] = train[where] & (~target);
			break;
			case 3:
			train[where] = train[where] << 1;
			break;
			case 4:
			train[where] = train[where] >> 1;
			break;
		}

		train[where] = train[where] & FULL_CAR;
	}

	char used[1048576] = { 0 };
	int i, result = 0;
	for (i = 0; i < car; i++) {
		int passengers = train[i];
		if (!used[passengers]) {
			used[passengers] = 1;
			result++;
		}
	}

	printf("%d\n", result);

	free(train);
}
