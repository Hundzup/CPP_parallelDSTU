#include <mpi.h>
#include <omp.h>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string> 

// Функция для вычисления интеграла методом прямоугольников
double integrate(double a, double b, int N, int rank, int size) {
    double h = (b - a) / N;
    double sum = 0.0;
    int local_N = N / size; // Количество интервалов на процесс
    int start = rank * local_N;
    int end = start + local_N;

    #pragma omp parallel for reduction(+:sum)
    for (int i = start; i < start + local_N; ++i) {
        double x = a + (i + 0.5) * h; // Центр интервала
        sum += 4.0 / (1.0 + x * x); // Интегрируемая функция
    }

    return sum * h;
}

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Проверка аргументов
    if (argc != 2) {
        if (rank == 0) {
            std::cerr << "Usage: " << argv[0] << " N" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    int N = std::stoi(argv[1]);

    // Проверка: N должно делиться на количество процессов
    if (N % size != 0) {
        if (rank == 0) {
            std::cerr << "Error: N must be divisible by the number of processes." << std::endl;
        }
        MPI_Finalize();
        return 1;
    }

    // Вычисление локальной суммы в каждом процессе
    double local_sum = integrate(0.0, 1.0, N, rank, size);

    // Сборка сумм из всех процессов
    double global_sum;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Вывод результата только на процессе 0
    if (rank == 0) {
        std::cout << std::fixed << std::setprecision(15);
        std::cout << "Computed pi: " << global_sum << std::endl;
    }

    MPI_Finalize();
    return 0;
}