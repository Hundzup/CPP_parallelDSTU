#include <mpi.h>
#include <iostream>
#include <vector>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int n;
    if (rank == 0){
        std::cout << "Enter n:" << std::endl;
        std::cin >> n;
    }
    MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if (size != n){
        if (rank == 0){
            std::cerr << "Error size != n  !!!" << std::endl;
        }
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    std::vector<double> A(n*n), B(n*n), C(n*n);

    if (rank == 0){
        std::cout << "Enter a matrix A (" << n*n << ") elem" << std::endl;
        for (int i = 0; i < n*n; i++){
            std::cin >> A[i];
        }
        
        std::cout << "Enter a matrix B (" << n*n << ") elem" << std::endl;
        for (int i = 0; i < n*n; i++){
            std::cin >> B[i];
        }
    }
    
    std::vector<double> local_A(n);
    MPI_Scatter(A.data(), n, MPI_DOUBLE, local_A.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    MPI_Bcast(B.data(), n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    std::vector<double> local_C(n, 0.0);
    for (int j=0; j<n; j++){
        for (int k=0; k<n; k++){
            local_C[j] += local_A[k]*B[k*n + j];
        }
    }

    MPI_Gather(local_C.data(), n, MPI_DOUBLE, C.data(), n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    if (rank == 0){
        std::cout << "Rezult: " << std::endl;
        for (int i = 0; i<n*n ; i++){
            if (i%n==0) std::cout << std::endl;
            std::cout << C[i] << " ";
        }
        std::cout << std::endl;
    }


    MPI_Finalize();
    return 0;
}