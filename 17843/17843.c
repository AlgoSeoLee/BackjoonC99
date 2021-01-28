#include <stdio.h>
#include <stdlib.h>

int comparator(const void *pa, const void *pb) {
	double a = *(double*)pa;
	double b = *(double*)pb;

	if (a < b)
		return -1;
	else if (a > b)
		return 1;

	return 0;
}

int main() {
	int c;
	scanf("%d", &c);

	while (c--) {
		double hour, min, sec;
		scanf("%lf %lf %lf", &hour, &min, &sec);

		min = min + sec / 60;
		hour = hour * 5 + min / 12;

		double timeAt[3] = {
			hour,
			min,
			sec
		};

		qsort(timeAt, 3, sizeof(double), comparator);

		double low2mid = timeAt[1] - timeAt[0];
		double mid2high = timeAt[2] - timeAt[1];
		printf("%lf %lf\n", low2mid, mid2high);
		double result;
		if (low2mid < mid2high)
			result = low2mid;
		else
			result = mid2high;

		result *= 6;

		printf("%lf\n", result);
	}

	return 0;
}
