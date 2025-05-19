#include "mpi.h"
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int MAX_STRING_LENGHT = 128;
    if (rank == 0){
        char message[MAX_STRING_LENGHT] = "Hello World!";
        int length = strlen(message);
        MPI_Send(&length, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(message, length+1, MPI_CHAR, 1, 0, MPI_COMM_WORLD);
    }
    if (rank == 1){
        int length;
        char recvmessage[MAX_STRING_LENGHT];
        MPI_Recv(&length, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(recvmessage, length+1, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Received message " << recvmessage << std::endl;
    }


    MPI_Finalize();
    return 0;
}