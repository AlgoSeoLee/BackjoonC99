#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/18110 Solved.ac <실버 4>

void MergeSort(int* arr, int length);
int* _Copy(int* arr, int start, int end);

void MergeSort(int* arr, int length) {
    if (length == 1) {
        return;
    }

    int half = length / 2;
    int rest = (length - half);
    int* left = _Copy(arr, 0, half);
    int* right = _Copy(arr, half, length);
    MergeSort(left, half);
    MergeSort(right, rest);

    int leftIndex = 0;
    int rightIndex = 0;
    int mainIndex = 0;

    while (leftIndex < half && rightIndex < rest) {
        if (left[leftIndex] <= right[rightIndex]) {
            arr[mainIndex] = left[leftIndex];
            leftIndex++;
        } else {
            arr[mainIndex] = right[rightIndex];
            rightIndex++;
        }
        mainIndex++;
    }

    while (leftIndex < half) {
        arr[mainIndex] = left[leftIndex];
        leftIndex++;
        mainIndex++;
    }

    while (rightIndex < rest) {
        arr[mainIndex] = right[rightIndex];
        rightIndex++;
        mainIndex++;
    }

    free(left);
    free(right);
}

int* _Copy(int *arr, int start, int end) {
    int length = end - start;
    int* copy = (int*)malloc(sizeof(int) * length);

    int i;
    for (i = 0; i < length; i++) {
        copy[i] = arr[start+i];
    }

    return copy;
}

int main() {
	int cases;
	int scores[300000] = {0};

	scanf("%d", &cases);
	if (cases == 0) {
		printf("0\n");
		return 0;
	}

	int i;
	for (i = 0; i < cases; i++)
		scanf("%d", scores + i);

	MergeSort(scores, cases);
	double sum = 0;
	int outliar = round(cases * 0.15);
	for (i = outliar; i < cases - outliar; i++) {
		sum += scores[i];
	}

	int result = round(sum / (cases - outliar * 2));
	printf("%d\n", result);

	return 0;
}
