#include <omp.h>
#include <iostream>

int main()
{
    int a = 1;
    int b = 2;

    printf("Before 1 parallel area: a = %d, b = %d \n", a, b);

#pragma omp parallel private(a) firstprivate(b) num_threads(2)
    {
        a = 1;
        int num = omp_get_thread_num();
        a += num;
        b += num;

        printf("In 1 parallel area : a = %d, b = %d \n", a, b);
    }

    printf("After 1 parallel area : a = %d, b = %d \n", a, b);

    printf("Before 2 parallel area: a = %d, b = %d \n", a, b);

#pragma omp parallel num_threads(4) shared(a) private(b)
    {
        b = 2;
        int num = omp_get_thread_num();
        a -= num;
        b -= num;

        printf("In 2 parallel area : a = %d, b = %d \n", a, b);
    }

    printf("After 2 parallel area : a = %d, b = %d", a, b);
}
