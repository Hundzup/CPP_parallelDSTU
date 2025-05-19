#include <mpi.h>
#include <iostream>

int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int N;
    if (rank == 0) {
        std::cout << "Enter N: ";
        std::cin >> N;
    }

    // Рассылаем N всем процессам
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    double dx = 1.0 / N;
    double local_sum = 0.0;

    // Вычисление локальной суммы
    int chunk_size = N / size;
    int start = rank * chunk_size;
    int end = (rank == size - 1) ? N : start + chunk_size;

    for (int i = start; i < end; i++) {
        double x = (i + 0.5) * dx;
        local_sum += 4.0 / (1.0 + x * x);
    }

    // Создание окна для сбора данных в процессе 0
    double* win_buffer = nullptr;
    MPI_Win win;
    if (rank == 0) {
        MPI_Alloc_mem(size * sizeof(double), MPI_INFO_NULL, &win_buffer);
        for (int i = 0; i < size; i++) {
            win_buffer[i] = 0.0;
        }
        MPI_Win_create(win_buffer, size * sizeof(double), sizeof(double), MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    } else {
        MPI_Win_create(nullptr, 0, 1, MPI_INFO_NULL, MPI_COMM_WORLD, &win);
    }

    // Запись локальных сумм в окно процесса 0
    MPI_Win_lock(MPI_LOCK_EXCLUSIVE, 0, 0, win);
    MPI_Put(&local_sum, 1, MPI_DOUBLE, 0, rank, 1, MPI_DOUBLE, win);
    MPI_Win_unlock(0, win);

    // Синхронизация всех процессов
    MPI_Barrier(MPI_COMM_WORLD);

    // Процесс 0 суммирует результаты и выводит π
    if (rank == 0) {
        double global_sum = 0.0;
        for (int i = 0; i < size; i++) {
            global_sum += win_buffer[i];
        }
        double pi = global_sum * dx;
        std::cout.precision(15);
        std::cout << "Calculated Pi: " << pi << std::endl;

        // Освобождение ресурсов
        MPI_Free_mem(win_buffer);
    }

    MPI_Win_free(&win);
    MPI_Finalize();
    return 0;
}