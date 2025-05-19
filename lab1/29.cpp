#include <omp.h>
#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>

int main(int argc, char* argv[]) {
    long long N = 100;       
    int num_threads = 1;      
    
    if (argc > 1) {
        N = std::stoll(argv[1]);
    }
    if (argc > 2) {
        num_threads = std::stoi(argv[2]);
    }

    double start = omp_get_wtime();
    double h = 1.0 / N;       
    double sum = 0.0;

    #pragma omp parallel for num_threads(num_threads) reduction(+:sum)
    for (long long i = 0; i < N; ++i) {
        
        double x = (i + 0.5) * h;


        sum += 4.0 / (1.0 + x * x);
    }


    double pi = sum * h;
    double end = omp_get_wtime();

    std::cout << "Rezult pi: " << pi << std::endl;
    std::cout << "Time run: " << end - start << " second" << std::endl;

    return 0;
}