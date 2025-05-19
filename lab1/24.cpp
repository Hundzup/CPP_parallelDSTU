#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N = 0;    
    if (rank == 0){
        std::cout << "Enter N:" << std::endl;
        std::cin >> N;
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double dx = 1.0 / N;
    double local_sum = 0.0;

    for (int i = rank; i < N; i+=size){
        double x = (i + 0.5) *dx;
        local_sum += 4.0 / (1.0 + x * x);
    }

    double global_sum;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0){
        double pi = global_sum * dx;
        std::cout << "Calculated pi: " << pi;
    }


    MPI_Finalize();
    return 0;
}