#include <iostream>
#include <mpi.h>

const int SIZE = 10;
int main(int argc, char** argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int vector[SIZE];
    int matrix[SIZE][SIZE];
    int localResult[SIZE];

    if (rank == 0) {
        for (int i = 0; i < SIZE; ++i) {
            vector[i] = i + 2;
            for (int j = 0; j < SIZE; ++j) {
                matrix[i][j] = 5 * i + j;
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }

        std::cout << "Vector:\n";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;

        for (int i = 1; i < size; ++i) {
            MPI_Send(vector, SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(matrix, SIZE * SIZE, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
    }
    else {
        MPI_Recv(vector, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(matrix, SIZE * SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    for (int i = 0; i < SIZE; ++i) {
        localResult[i] = 0;
        for (int k = 0; k < SIZE; ++k) {
            localResult[i] += matrix[i][k] * vector[k];
        }
    }

    if (rank == 0) {
        int result[SIZE];

        for (int i = 1; i < size; ++i) {
            MPI_Recv(result, SIZE, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            for (int j = 0; j < SIZE; ++j) {
                result[j] = localResult[j];
            }
        }

        std::cout << "Result:\n";
        for (int i = 0; i < SIZE; ++i) {
            std::cout << result[i] << " ";
        }
        std::cout << std::endl;
    }
    else {
        MPI_Send(localResult, SIZE, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}