#include <stdio.h>
#include <string.h>

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

int main() {
	char exp[101];
	scanf("%s", exp);

	int length = strlen(exp);
	int i;
	for (i = 0; i < length; i++) {
		char single = exp[i];
		if (single < 58 && single >= 48) {
			int data = single - 48;
			push(data);
		} else {
			int a, b, result;
			b = pop();
			a = pop();
			switch (single) {
			case '+':
				result = a + b;
				break;
			case '-':
				result = a - b;
				break;
			case '*':
				result = a * b;
				break;
			case '/':
				result = a / b;
				break;
			}
			push(result);
		}
	}

	printf("%d\n", pop());
}
