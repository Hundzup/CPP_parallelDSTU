#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    MPI_Comm parent;
    MPI_Comm_get_parent(&parent);

    if (parent == MPI_COMM_NULL) {
        if (world_rank == 0) {
            int n;
            std::cout << "Enter n: ";
            std::cin >> n;

            MPI_Comm child_comm;
            MPI_Comm_spawn(argv[0], MPI_ARGV_NULL, n, MPI_INFO_NULL, 0, MPI_COMM_SELF, &child_comm, MPI_ERRCODES_IGNORE);

            MPI_Comm merged_comm;
            MPI_Intercomm_merge(child_comm, 0, &merged_comm);

            int merged_rank, merged_size;
            MPI_Comm_rank(merged_comm, &merged_rank);
            MPI_Comm_size(merged_comm, &merged_size);

            std::cout << "I am " << merged_rank << " process from " << merged_size 
                      << " processes! My parent is 0" << std::endl;

            MPI_Comm_free(&merged_comm);
        }
    } else {
        MPI_Comm merged_comm;
        MPI_Intercomm_merge(parent, 1, &merged_comm);

        int merged_rank, merged_size;
        MPI_Comm_rank(merged_comm, &merged_rank);
        MPI_Comm_size(merged_comm, &merged_size);

        std::cout << "I am " << merged_rank << " process from " << merged_size 
                  << " processes! My parent is 0" << std::endl;

        MPI_Comm_free(&merged_comm);
    }

    MPI_Finalize();
    return 0;
}