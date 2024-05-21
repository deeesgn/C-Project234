#include "kmeans.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Конструктор
KMeans::KMeans(int k, int max_iterations) : k(k), max_iterations(max_iterations) {}

// Инициализация центроидов случайным образом
void KMeans::initializeCentroids() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, points.size() - 1);

    for (int i = 0; i < k; ++i) {
        int idx = dis(gen);
        clusters.emplace_back(points[idx].coordinates);
    }
}

// Метод для вычисления расстояния между двумя точками (Евклидово расстояние)
double KMeans::calculateDistance(const Point& p1, const Point& p2) {
    double sum = 0.0;
    for (size_t i = 0; i < p1.coordinates.size(); ++i) {
        sum += std::pow(p1.coordinates[i] - p2.coordinates[i], 2);
    }
    return std::sqrt(sum);
}

// Назначение точек кластерам
void KMeans::assignPointsToClusters() {
    for (auto& point : points) {
        double min_distance = std::numeric_limits<double>::max();
        int best_cluster = -1;

        for (size_t i = 0; i < clusters.size(); ++i) {
            double distance = calculateDistance(point, Point(clusters[i].centroid));
            if (distance < min_distance) {
                min_distance = distance;
                best_cluster = i;
            }
        }

        point.cluster = best_cluster;
        clusters[best_cluster].points.push_back(point);
    }
}

// Обновление центроидов кластеров
void KMeans::updateCentroids() {
    for (auto& cluster : clusters) {
        std::vector<double> new_centroid(cluster.centroid.size(), 0.0);

        for (const auto& point : cluster.points) {
            for (size_t i = 0; i < point.coordinates.size(); ++i) {
                new_centroid[i] += point.coordinates[i];
            }
        }

        for (size_t i = 0; i < new_centroid.size(); ++i) {
            new_centroid[i] /= cluster.points.size();
        }

        cluster.centroid = new_centroid;
    }
}

// Очистка кластеров
void KMeans::clearClusters() {
    for (auto& cluster : clusters) {
        cluster.points.clear();
    }
}

// Запуск алгоритма k-means
void KMeans::fit(std::vector<Point>& data) {
    points = data;
    initializeCentroids();

    for (int i = 0; i < max_iterations; ++i) {
        clearClusters();
        assignPointsToClusters();
        updateCentroids();
    }
}

// Получение результатов
std::vector<int> KMeans::getLabels() {
    std::vector<int> labels;
    for (const auto& point : points) {
        labels.push_back(point.cluster);
    }
    return labels;
}

// Вычисление ошибки кластера (сумма квадратов расстояний от точек до центроида)
double KMeans::calculateError() {
    double total_error = 0.0;
    for (const auto& cluster : clusters) {
        for (const auto& point : cluster.points) {
            total_error += std::pow(calculateDistance(point, Point(cluster.centroid)), 2);
        }
    }
    return total_error;
}

// Функция для запуска алгоритма k-means
std::pair<std::vector<std::vector<double>>, std::vector<int>> run_kmeans(const std::vector<std::vector<double>>& data, int num_clusters, int max_iters) {
    // Инициализация данных и параметров
    std::vector<Point> points;
    for (const auto& d : data) {
        points.emplace_back(d);
    }

    KMeans kmeans(num_clusters, max_iters);
    kmeans.fit(points);

    // Получение результатов
    std::vector<int> labels = kmeans.getLabels();
    std::vector<std::vector<double>> centroids;
    for (const auto& cluster : kmeans.getClusters()) {
        centroids.push_back(cluster.centroid);
    }

    return {centroids, labels};
}

// Функция для многократного запуска k-means и выбора лучшего результата
std::tuple<std::vector<std::vector<double>>, std::vector<int>, double> run_kmeans_multiple(const std::vector<std::vector<double>>& data, int num_clusters, int max_iters, int num_runs) {
    double best_error = std::numeric_limits<double>::max();
    std::vector<std::vector<double>> best_centroids;
    std::vector<int> best_labels;

    for (int run = 0; run < num_runs; ++run) {
        auto [centroids, labels] = run_kmeans(data, num_clusters, max_iters);

        // Создать новый экземпляр KMeans для оценки ошибки
        std::vector<Point> points;
        for (const auto& d : data) {
            points.emplace_back(d);
        }

        KMeans kmeans(num_clusters, max_iters);
        kmeans.fit(points);

        double error = kmeans.calculateError();
        std::cout << "Run " << run + 1 << " error: " << error << std::endl; // Вывод ошибки после каждого запуска

        if (error < best_error) {
            best_error = error;
            best_centroids = centroids;
            best_labels = labels;
        }
    }

    return {best_centroids, best_labels, best_error};
}
