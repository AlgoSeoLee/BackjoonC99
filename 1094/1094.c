#include <stdio.h>

// https://www.acmicpc.net/problem/1094 막대기 <실버 5> <발표>

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
	int target, rest = 64;
	scanf("%d", &target);

	push(64);
	while(rest != target) {
		int slice = pop() / 2;
		push(slice);
		if (rest - slice < target) 
			push(slice);
		else
			rest = rest - slice;
	}

	printf("%d\n", stack.length);

	return 0;
}
