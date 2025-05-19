#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <string>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int n_threads = 2; // Значение по умолчанию
    if (argc > 1) {
        n_threads = std::stoi(argv[1]); // Задаем через первый аргумент
    }

    MPI_Barrier(MPI_COMM_WORLD);

    #pragma omp parallel num_threads(n_threads)
    {
        int thread_num = omp_get_thread_num();

        #pragma omp critical
        {
            int hybrid_threads = world_size * n_threads;
            std::cout << "I am " << thread_num
                      << " thread from " << world_rank
                      << " process. Number of hybrid threads = " << hybrid_threads << std::endl;
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();

    return 0;
}