#include<stdio.h>
#include<string.h>

// https://www.acmicpc.net/problem/9012 괄호 <실버 4>

struct Stack {
	int length;
	int array[100];
} stack;

void push(int data) {
	stack.array[stack.length] = data;
	stack.length++;
}

int pop() {
	int data = stack.array[stack.length - 1];
	stack.length--;
	return data;
}

int empty() {
	return stack.length == 0 ? 1 : 0;
}

int main() {
	int c;
	scanf("%d", &c);
	while(c--) {
		char line[100] = {0};
		scanf("%s", line);
		int len = strlen(line);
		int invalid = 0;
		int i;
		for (i = 0; i < len; i++) {
			switch (line[i]) {
				case '(':
				push(0);break;
				case ')':
				if (empty())
					invalid = 1;
				else
					pop();
				break;
			}

			if (invalid)
				break;
		}

		if (!empty())
			invalid = 1;

		if (invalid) {
			printf("NO\n");
			while (!empty())
				pop();
		} else
			printf("YES\n");
	}
}
