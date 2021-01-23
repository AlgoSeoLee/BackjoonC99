#include <stdio.h>
#include <string.h>

// https://www.acmicpc.net/problem/6581 HTML <실버 1>

#define MAXIMUM 80

int main() {
	char word[MAXIMUM + 1] = { '\0' };
	char word_length = 0;
	char line[MAXIMUM + 1] = { '\0' };
	char line_length = 0;

	char input = getchar();
	while (input != EOF) {
		switch (input) {
		case '\n':
		case '\t':
		case ' ':
			if (word_length != 0) {
				int is_next = 0;
				int is_full = 0;

				if (strcmp(word, "<br>") == 0) {
					is_next = 1;
				} else if (strcmp(word, "<hr>") == 0) {
					if (line_length != 0)
						printf("%s\n", line);
					memset(line, '-', MAXIMUM);
					is_next = 1;
				} else if (line_length + word_length + 1 > MAXIMUM) {
					is_next = 1;
					is_full = 1;
				} else {
					if (line_length != 0) {
						line[line_length] = ' ';
						line_length++;
					}
					strcat(line, word);
					line_length += word_length;
				}

				if (is_next) {
					printf("%s\n", line);
					line_length = 0;
					memset(line, '\0', MAXIMUM);
					if (is_full) {
						strcat(line, word);
						line_length = word_length;
					}
				}

				word_length = 0;
				memset(word, '\0', MAXIMUM);
			}
			break;
		default:
			word[word_length] = input;
			word_length++;
		}

		input = getchar();
	}

	printf("%s\n", line);

	return 0;
}
