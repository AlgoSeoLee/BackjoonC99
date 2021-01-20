#include <stdlib.h>

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

int* _Copy(int* arr, int start, int end) {
    int length = end - start;
    int* copy = (int*)malloc(sizeof(int) * length);

    int i;
    for (i = 0; i < length; i++) {
        copy[i] = arr[start+i];
    }

    return copy;
}
