#include <stdio.h>

void divmod(int x, int y, int* div, int* mod) {
	*div = x / y;
	*mod = x % y;
}

int main() {
    int amount;
    int large, small;
    int large_after, small_after;
    int offset = 0;

    scanf("%d", &amount);
    divmod(amount, 5, &large, &large_after);
    if (large_after != 0) {
        for (offset = 0; offset <= large; offset++) {
            divmod(large_after + (offset * 5), 3, &small, &small_after);
            if (small_after == 0) {
                break;
            }
        }
        if (small_after != 0) {
            printf("%d\n", -1);
        } else {
            printf("%d\n", small + large - offset);
        }
    } else {
        printf("%d\n", large);
    }
}
