#include <iostream>
#include <omp.h>

int main() {
    omp_set_num_threads(8);

#pragma omp parallel
        std::cout << "Thread " << omp_get_thread_num() << " of " << omp_get_num_threads() << ": " << "Hello world \n";
}
