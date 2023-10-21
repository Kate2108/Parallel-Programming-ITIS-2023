#include <iostream>

int main()
{
    int a[] {3, 2, 9, 4, 8, 12, 5, 31, 19, 10};
    int b[] {8, 5, 1, 6, 7, 3, 14, 21, 25, 20};

    float avg_a = 0;
    float avg_b = 0;

#pragma omp parallel for reduction(+:avg_a) reduction(+:avg_b)
    for (int i = 0; i < 10; i++) {
        avg_a += a[i];
        avg_b += b[i];
    }

    avg_a = avg_a / 10;
    avg_b = avg_b / 10;

    printf("Average of a = %f, average of b  = %f \n", avg_a, avg_b);

    char sign = '=';

    if (avg_a > avg_b) {
        printf("%f %c %f", avg_a, '>', avg_b);
    }
    else if (avg_a < avg_b) {
        printf("%f %c %f", avg_a, '<', avg_b);
    }
    else {
        printf("%f %c %f", avg_a, '=', avg_b);
    }
}
