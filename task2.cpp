#include <iostream>
#include <omp.h>

int main()
{
    int threads = 3;

    omp_set_num_threads(threads);

#pragma omp parallel if (omp_get_max_threads() > 1)
    {
        int all_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        printf("1 parallel area: thread %d of %d \n", thread_id, all_threads);
    }

    threads = 1;

    omp_set_num_threads(threads);

#pragma omp parallel if (omp_get_max_threads() > 1)
    {
        int all_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        printf("2 parallel area: thread %d of %d \n", thread_id, all_threads);
    }
}
