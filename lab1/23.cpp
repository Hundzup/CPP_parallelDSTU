#include <string.h>
#include <iostream>
#include <mpi.h>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    const int MAX_STRING_LENGHT = 1000;
    char str[MAX_STRING_LENGHT];
    int n;
    int *counts = NULL;
    int *global_counts = NULL;

    if (rank == 0){
        std::cout << "Enter a string: " << std::endl;
        std::cin.getline(str, MAX_STRING_LENGHT);
        n = std::strlen(str);
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    counts = new int[256]();
    global_counts = new int[256]();

    MPI_Bcast(str, n, MPI_CHAR, 0, MPI_COMM_WORLD);

    int chunk_size = n / size;
    int start = rank*chunk_size;
    int end = (rank == size - 1) ? n : start + chunk_size;

    for (int i = start; i < end; i++){
        counts[static_cast<unsigned char>(str[i])]  ++;
    }

    MPI_Reduce(counts, global_counts, 256, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0){
        std::cout << "Character count" << std::endl;
        for (int i = 0; i < 256; i++){
            if (global_counts[i] > 0){
                std::cout << static_cast<char>(i) << " " << global_counts[i] << std::endl;
            }
        }
    }

    MPI_Finalize();
    return 0;
}