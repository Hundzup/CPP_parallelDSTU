#include <mpi.h>
#include <iostream>
#include <string>
#include <cstring>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    MPI_Comm even_comm;
    int color = (rank % 2 == 0) ? 0 : MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD, color, rank, &even_comm);

    std::string message;
    int message_length = 0;

    if (rank == 0) {
        std::cout << "Enter message: ";
        std::cin >> message;
        message_length = message.size();
    }

    MPI_Bcast(&message_length, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Выделяем буфер для сообщения
    char* buffer = new char[message_length + 1];
    if (rank == 0) {
        std::strcpy(buffer, message.c_str());
    }

    if (even_comm != MPI_COMM_NULL) {
        int even_rank, even_size;
        MPI_Comm_rank(even_comm, &even_rank);
        MPI_Comm_size(even_comm, &even_size);

        MPI_Bcast(buffer, message_length + 1, MPI_CHAR, 0, even_comm);

        std::cout << "MPI_COMM_WORLD: " << rank << " from " << size
                  << ". New comm: " << even_rank << " from " << even_size
                  << ". Message = " << buffer << std::endl;
    } else {
        std::cout << "MPI_COMM_WORLD: " << rank << " from " << size
                  << ". New comm: NO from NO. Message = NO" << std::endl;
    }

    delete[] buffer;

    if (even_comm != MPI_COMM_NULL) {
        MPI_Comm_free(&even_comm);
    }

    MPI_Finalize();
    return 0;
}