
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

