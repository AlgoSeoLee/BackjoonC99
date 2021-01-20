void QuickSort(int* arr, int length);
void _QuickSort(int* arr, int start, int end);
int _SelectPivot(int* arr, int start, int end, int index);

void QuickSort(int* arr, int length) {
    _QuickSort(arr, 0, length - 1);
}

void _QuickSort(int* arr, int start, int end) {
    if (start >= end) {
        return;
    }

    int index = (end - start) % rand();
    int pivot = _SelectPivot(arr, start, end, start+index);
    _QuickSort(arr, start, pivot - 1);
    _QuickSort(arr, pivot + 1, end);
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int _SelectPivot(int* arr, int start, int end, int index) {
    const int pivot = end;
    swap(arr+index, arr+pivot);

    int target = arr[pivot];
    int smaller = start;

    int i;
    for (i = start; i < end; i++) {
        if (arr[i] <= target) {
            swap(arr+i, arr+smaller);
            smaller++;
        }
    }

    swap(arr+pivot, arr+smaller);

    return smaller;
}

