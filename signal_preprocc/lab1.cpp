#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <tuple>

const double PI = 3.14159265358979323846;

// Функция для генерации гармоники
std::vector<double> generateHarmonic(int numPoints, double amplitude, double frequency, double phase, double deltaT) {
    std::vector<double> harmonic(numPoints);
    for (int i = 0; i < numPoints; ++i) {
        double t = i * deltaT;
        harmonic[i] = amplitude * sin(2 * PI * frequency * t + phase);
    }
    return harmonic;
}

int main() {
    // Задаем параметры заранее
    int numHarmonics = 10;          // Количество гармоник
    int numPoints = 10000;          // Количество точек
    double samplingFrequency = 1000.0; // Частота дискретизации (Гц)
    double iMax = 5.0;             // Максимальная амплитуда

    double deltaT = 1.0 / samplingFrequency; // Шаг времени

    // Параметры гармоник (амплитуда, частота, начальная фаза)
    std::vector<std::tuple<double, double, double>> harmonicParams = {
        {2.0, 50.0, 0.0},           // Гармоника 1: амплитуда = 2, частота = 50 Гц, фаза = 0
        {1.5, 100.0, PI / 4},       // Гармоника 2: амплитуда = 1.5, частота = 100 Гц, фаза = π/4
        {1.0, 200.0, PI / 2},       // Гармоника 3: амплитуда = 1, частота = 200 Гц, фаза = π/2
        {0.8, 300.0, 3 * PI / 4},   // Гармоника 4: амплитуда = 0.8, частота = 300 Гц, фаза = 3π/4
        {0.6, 400.0, PI},           // Гармоника 5: амплитуда = 0.6, частота = 400 Гц, фаза = π
        {0.5, 500.0, PI / 6},       // Гармоника 6: амплитуда = 0.5, частота = 500 Гц, фаза = π/6
        {0.4, 600.0, PI / 3},       // Гармоника 7: амплитуда = 0.4, частота = 600 Гц, фаза = π/3
        {0.3, 700.0, 2 * PI / 3},   // Гармоника 8: амплитуда = 0.3, частота = 700 Гц, фаза = 2π/3
        {0.2, 800.0, 5 * PI / 6},   // Гармоника 9: амплитуда = 0.2, частота = 800 Гц, фаза = 5π/6
        {0.1, 900.0, PI / 8}        // Гармоника 10: амплитуда = 0.1, частота = 900 Гц, фаза = π/8
    };

    // Векторы для хранения данных
    std::vector<std::vector<double>> harmonics(numHarmonics, std::vector<double>(numPoints));
    std::vector<double> resultSignal(numPoints, 0.0);

    // Генерация гармоник
    for (int i = 0; i < numHarmonics; ++i) {
        double amplitude = std::get<0>(harmonicParams[i]);
        double frequency = std::get<1>(harmonicParams[i]);
        double phase = std::get<2>(harmonicParams[i]);

        harmonics[i] = generateHarmonic(numPoints, amplitude, frequency, phase, deltaT);

        // Суммирование гармоник
        for (int j = 0; j < numPoints; ++j) {
            resultSignal[j] += harmonics[i][j];
        }
    }

    // Сохранение данных в файл
    std::ofstream outputFile("signal_data.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return 1;
    }

    outputFile << "Time\tResultSignal\n";
    for (int i = 0; i < numPoints; ++i) {
        double t = i * deltaT;
        outputFile << t << "\t" << resultSignal[i] << "\n";
    }
    outputFile.close();

    std::cout << "Data saved to signal_data.txt" << std::endl;

    return 0;
}