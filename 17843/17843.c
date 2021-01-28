#include <stdio.h>
#include <math.h>

// https://www.acmicpc.net/problem/17843 시계 <실버 5>

double calcAngle(double hour, double min, double sec) {
	min = min + sec / 60;
	hour = hour * 5 + min / 12;

	double timeAt[6] = {
		hour,
		min,
		sec,
		hour + 60,
		min + 60,
		sec + 60
	};

	double result = 60;
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 6; j++) {
			if (j == i)
				continue;

			double tmp = fabs(timeAt[i] - timeAt[j]);
			if (tmp < result)
				result = tmp;
		}
	}

	result *= 6;

	return result;
}


int main() {
	int c;
	scanf("%d", &c);

	while (c--) {
		double hour, min, sec;
		scanf("%lf %lf %lf", &hour, &min, &sec);

		double result = calcAngle(hour, min, sec);

		printf("%lf\n", result);
	}

	return 0;
}
