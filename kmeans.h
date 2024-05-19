#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include <cmath>
#include <limits>
#include <random>
#include <algorithm>
#include <tuple> // Добавляем для использования std::tuple

// Структура для представления точки данных
struct Point {
    std::vector<double> coordinates;
    int cluster;

    Point(std::vector<double> coords) : coordinates(coords), cluster(-1) {}
};

// Структура для представления кластера
struct Cluster {
    std::vector<double> centroid;
    std::vector<Point> points;

    Cluster(std::vector<double> init_centroid) : centroid(init_centroid) {}
};

// Класс для алгоритма k-means
class KMeans {
private:
    int k; // Количество кластеров
    int max_iterations; // Максимальное количество итераций
    std::vector<Point> points; // Все точки данных
    std::vector<Cluster> clusters; // Все кластеры

    // Инициализация центроидов
    void initializeCentroids();

    // Назначение точек кластерам
    void assignPointsToClusters();

    // Обновление центроидов кластеров
    void updateCentroids();

    // Вычисление расстояния между двумя точками
    double calculateDistance(const Point& p1, const Point& p2);

    // Очистка кластеров
    void clearClusters();

public:
    // Конструктор
    KMeans(int k, int max_iterations);

    // Запуск алгоритма k-means
    void fit(std::vector<Point>& data);

    // Получение результатов
    std::vector<int> getLabels();

    // Получение кластеров для дальнейшего использования
    const std::vector<Cluster>& getClusters() const { return clusters; }

    // Вычисление ошибки кластера (сумма квадратов расстояний от точек до центроида)
    double calculateError();
};

// Функция для запуска алгоритма k-means
std::pair<std::vector<std::vector<double>>, std::vector<int>> run_kmeans(const std::vector<std::vector<double>>& data, int num_clusters, int max_iters);

// Функция для многократного запуска k-means и выбора лучшего результата
std::tuple<std::vector<std::vector<double>>, std::vector<int>, double> run_kmeans_multiple(const std::vector<std::vector<double>>& data, int num_clusters, int max_iters, int num_runs);

#endif // KMEANS_H
