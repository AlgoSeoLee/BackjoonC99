#include <stdio.h>
#include <stdlib.h>

// https://www.acmicpc.net/problem/1920 수 찾기 <실버 4>

int comparator(const void* pa, const void* pb) {
    const int* a = pa;
    const int* b = pb;

    if (*a < *b)
        return -1;
    else if (*a > *b)
        return 1;

    return 0;
}

int binarySearch(int* arr, size_t length, int target) {
    size_t start = 0;
    size_t end = length - 1;

    while (start <= end) {
        size_t mid = (start + end) / 2;
        int* tester = arr + mid;

        if (*tester == target)
            return mid;
        else if (*tester > target)
            end = mid - 1;
        else
            start = mid + 1;
    }

    return -1;
}

int main() {
    int note1_length;
    scanf("%d", &note1_length);
    int note1[100001];

    int i;
    for (i = 0; i < note1_length; i++)
        scanf("%d", note1 + i);

    qsort(note1, note1_length, sizeof(int), comparator);

    int t;
    scanf("%d", &t);
    int target;
    while (t--) {
        scanf("%d", &target);

        if (binarySearch(note1, note1_length, target) >= 0)
            printf("1\n");
        else
            printf("0\n");
    }
    
    return 0;
}
