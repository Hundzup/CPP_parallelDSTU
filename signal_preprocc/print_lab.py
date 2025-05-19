import numpy as np
import matplotlib.pyplot as plt

# Чтение данных из файла
data = np.loadtxt("reconstructed_signal.txt", skiprows=1)
time = data[:, 0]
signal = data[:, 1]

# Создание графика
plt.figure(figsize=(12, 6), dpi=100)

# Построение сигнала
plt.plot(
    time, signal,
    label="Result Signal",
    color="#1f77b4",  # Синий цвет
    linewidth=2,     # Толщина линии
    linestyle="-"    # Сплошная линия
)

# Настройка осей
plt.xlim(0, 1)  # Ограничение по оси X
plt.ylim(np.floor(np.min(signal)), np.ceil(np.max(signal)))  # Ограничение по оси Y
plt.xticks(np.linspace(0, 1, 11), fontsize=10)  # Метки по оси X
plt.yticks(fontsize=10)  # Метки по оси Y

# Добавление сетки
plt.grid(
    which="major", linestyle="--", linewidth=0.5, alpha=0.7, color="gray"
)
plt.minorticks_on()  # Включение второстепенных делений
plt.grid(
    which="minor", linestyle=":", linewidth=0.5, alpha=0.5, color="lightgray"
)

# Добавление заголовков и подписей
plt.title("Generated Signal", fontsize=14, fontweight="bold")
plt.xlabel("Time (s)", fontsize=12)
plt.ylabel("Amplitude", fontsize=12)

# Добавление легенды
plt.legend(loc="upper right", fontsize=10, frameon=True, shadow=True)

# Улучшение внешнего вида осей
ax = plt.gca()
ax.spines['top'].set_visible(False)    # Убираем верхнюю границу
ax.spines['right'].set_visible(False)  # Убираем правую границу
ax.spines['left'].set_linewidth(1.5)   # Утолщаем левую границу
ax.spines['bottom'].set_linewidth(1.5) # Утолщаем нижнюю границу

# Отображение графика
plt.tight_layout()  # Автоматическая корректировка макета
plt.show()
