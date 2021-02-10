#include <stdio.h>

// https://www.acmicpc.net/problem/2257 화학식량 <실버 3>

typedef struct _Stack {
	int length;
	int array[100];
} Stack;

void StackInit(Stack* stack) {
	stack->length = 0;
}

void StackPush(Stack* stack, int data) {
	stack->array[stack->length] = data;
	stack->length++;
}

int StackPop(Stack* stack) {
	int data = stack->array[stack->length - 1];
	stack->length--;
	return data;
}

int StackEmpty(Stack* stack) {
	return stack->length == 0 ? 1 : 0;
}

int calcCalorie(Stack* stack, char input) {
	int result = 0;
	if (input >= '2' && input <= '9')
		result = StackPop(stack) * (input - '0');
	else if (input == 'H')
		result = 1;
	else if (input == 'C')
		result = 12;
	else if (input == 'O')
		result = 16;

	StackPush(stack, result);
}

int inputObject() {
	int result = 0;
	Stack stack;
	StackInit(&stack);

	int input = getchar();
	while (input != EOF) {
		if (input == '(')
			StackPush(&stack, inputObject());
		else if (input == ')')
			break;
		else
			calcCalorie(&stack, input);

		input = getchar();
	}

	while (!StackEmpty(&stack))
		result += StackPop(&stack);

	return result;
}

int main() {
	printf("%d", inputObject());
	return 0;
}
