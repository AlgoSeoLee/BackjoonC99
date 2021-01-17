#include <stdio.h>
#include <string.h>

// https://www.acmicpc.net/problem/3568 iSharp <실버 5>

int main() {
	char input[120];
	gets(input);

	const char* delim = " ,;";
	char* target = strtok(input, delim);
	char* type = target;

	target = strtok(NULL,delim);
	for (; target != NULL; target = strtok(NULL,delim)){
		printf("%s", type);
		int start = 0;
		int length = strlen(target);
		for (; start < length; start++) {
			if (target[start] == '*' ||
				target[start] == '&' ||
				target[start] == '[')
				break;
		}

		int i;
		if (start < length) {
			i = length - 1;
			while (i >= start) {
				if (target[i] == ']') {
					printf("[]");
					i--;
				} else
					putc(target[i], stdout);

				i--;
			}
		}

		printf(" ");
		for (i = 0; i < start; i++)
			putc(target[i], stdout);

		printf(";\n");
	}

	return 0;
}
