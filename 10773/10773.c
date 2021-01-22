#include<stdio.h>

// https://www.acmicpc.net/problem/10773 제로 <실버 4>

struct Stack {
	int length;
	int array[100000];
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
		int score;
		scanf("%d", &score);
		if (score == 0 && !empty())
			pop();
		else if (score != 0)
			push(score);
	}

	int sum = 0;
	while (!empty())
		sum += pop();

	printf("%d", sum);

	return 0;
}

