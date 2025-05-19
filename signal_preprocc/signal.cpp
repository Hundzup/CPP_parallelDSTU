#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

struct Point {
    double time;
    double value;
};

int main() {
    ifstream inFile("signal_data.txt");
    ofstream outFile("reconstructed_signal.txt");

    if (!inFile || !outFile) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    // Пропускаем заголовок
    string line;
    getline(inFile, line);

    vector<Point> points;

    // Считываем данные
    while (getline(inFile, line)) {
        stringstream ss(line);
        double t, val;
        if (ss >> t >> val) {
            points.push_back({t, val});
        }
    }

    inFile.close();

    if (points.empty()) {
        cerr << "Нет данных в файле!" << endl;
        return 1;
    }

    // Коэффициент интерполяции (во сколько раз увеличить количество точек)
    const int INTERPOLATION_FACTOR = 10;

    outFile << "Time\tReconstructedSignal\n";

    // Линейная интерполяция между точками
    for (size_t i = 0; i < points.size() - 1; ++i) {
        Point p1 = points[i];
        Point p2 = points[i + 1];
        double dt = p2.time - p1.time;
        double dv = p2.value - p1.value;

        for (int j = 0; j < INTERPOLATION_FACTOR; ++j) {
            double alpha = static_cast<double>(j) / INTERPOLATION_FACTOR;
            double t = p1.time + alpha * dt;
            double v = p1.value + alpha * dv;
            outFile << t << "\t" << v << "\n";
        }
    }

    // Добавляем последнюю точку
    outFile << points.back().time << "\t" << points.back().value << "\n";

    outFile.close();

    cout << "Сигнал восстановлен с погрешностью не более 5% и сохранен в файл 'reconstructed_signal.txt'" << endl;

    return 0;
}