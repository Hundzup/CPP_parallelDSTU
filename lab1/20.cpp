#include <iostream>
#include "mpi.h"

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0){
        int to_send = 45;
        MPI_Request send_request;

        MPI_Isend(&to_send, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, &send_request);
        MPI_Wait(&send_request, MPI_STATUS_IGNORE);   
    }
    if (rank == 1){
        int to_recv;
        MPI_Request recv_request;
        MPI_Irecv(&to_recv, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &recv_request);
        MPI_Wait(&recv_request, MPI_STATUS_IGNORE);
        std::cout << "receive message: " << to_recv << std::endl;
    }
    MPI_Finalize();
    return 0;
}