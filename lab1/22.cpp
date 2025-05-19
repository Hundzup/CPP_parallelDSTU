#include <iostream>
#include "mpi.h"

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (int i = 0; i < size; i++){
        if (i == rank){
            continue;
        }
        int send_mess = rank;
        int recv_mess;
        MPI_Send(&send_mess, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        MPI_Recv(&recv_mess, 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "[" << rank << "]" << " receive from " << recv_mess << std::endl;
    }

    MPI_Finalize();
    return 0;
}