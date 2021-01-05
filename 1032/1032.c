#include <stdio.h>
#include <string.h>

int main() {
	int c, i, j, length = -1;
	char input[51], result[51];

	scanf("%d", &c);
	for (i = 0; i < c; i++) {
		scanf("%s", input);
		if (length == -1) {
			length = strlen(input);
			strcpy(result, input);
		} else {
			for (j = 0; j < length; j++) {
				if (result[j] != '?') {
					if (result[j] != input[j]) {
						result[j] = '?';
					}
				}
			}
		}
	}

	printf("%s", result);
	return 0;
}
