#include <stdio.h>
#include <string.h>

// https://www.acmicpc.net/problem/1475 방 번호 <실버 5>

int main() {
	char input[8];
	scanf("%s", input);

	char count[10] = { 0 };
	int length = strlen(input);
	int i;
	char toggle = 0;
	for (i = 0; i < length; i++) {
		char target = input[i] - '0';
		if (target == 6 || target == 9) {
			if (toggle) {
				toggle = 0;
				target = 9;
			} else {
				toggle = 1;
				target = 6;
			}
		}

		count[target]++;
	}

	char max = 0;
	for (i = 0; i < 10; i++) {
		if (max < count[i])
			max = count[i];
	}

	printf("%d\n", max);

	return 0;
}
