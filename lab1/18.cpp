#include "mpi.h"
#include <iostream>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    int message;
    if (rank == 0){
        MPI_Send(&rank, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Recv(&message, 1, MPI_INT, size-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "[0] : receive message '" << message << "'" << std::endl;
    } else{
        MPI_Recv(&message, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        if (rank+1 == size){
            MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }else{
            MPI_Send(&rank, 1, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
        }
        std::cout << "[" << rank << "] : receive message '" << message << "'" << std::endl;
    }

    MPI_Finalize();
    return 0;
}
