#include "kmeans.h"
#include <QFile>
#include <QTextStream>
#include <QVector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>

KMeans::KMeans(int k, int maxIterations) : k(k), maxIterations(maxIterations) {
    std::srand(std::time(nullptr));
}

void KMeans::fit(const std::vector<std::vector<double>> &data) {
    initialization(data);
    for (int iter = 0; iter < maxIterations; ++iter) {
        std::vector<std::vector<std::vector<double>>> clusters(k);
        for (const auto &point : data) {
            int centroidIndex = nearest(point);
            clusters[centroidIndex].push_back(point);
        }
        for (int i = 0; i < k; ++i) {
            if (!clusters[i].empty()) {
                centroids[i] = compute(clusters[i]);
            }
        }
    }
}

std::vector<int> KMeans::predict(const std::vector<std::vector<double>> &data) {
    std::vector<int> labels;
    for (const auto &point : data) {
        labels.push_back(nearest(point));
    }
    return labels;
}

std::vector<std::vector<double>> KMeans::getCentroids() {
    return centroids;
}

void KMeans::initialization(const std::vector<std::vector<double>> &data) {
    centroids.clear();
    std::vector<int> indices(data.size());
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), std::default_random_engine(std::rand()));
    for (int i = 0; i < k; ++i) {
        centroids.push_back(data[indices[i]]);
    }
}

int KMeans::nearest(const std::vector<double> &point) {
    double minDistance = std::numeric_limits<double>::max();
    int nearest = 0;
    for (int i = 0; i < k; ++i) {
        double distance = 0.0;
        for (size_t j = 0; j < point.size(); ++j) {
            distance += std::pow(point[j] - centroids[i][j], 2);
        }
        if (distance < minDistance) {
            minDistance = distance;
            nearest = i;
        }
    }
    return nearest;
}

std::vector<double> KMeans::compute(const std::vector<std::vector<double>> &cluster) {
    std::vector<double> centroid(cluster[0].size(), 0.0);
    for (const auto &point : cluster) {
        for (size_t i = 0; i < point.size(); ++i) {
            centroid[i] += point[i];
        }
    }
    for (size_t i = 0; i < centroid.size(); ++i) {
        centroid[i] /= cluster.size();
    }
    return centroid;
}

void loadCSV(const QString &filename, std::vector<std::vector<double>> &data, std::vector<QStringList> &originalData) {
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return;
    }

    QTextStream in(&file);
    data.clear();
    originalData.clear();
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');
        originalData.push_back(fields);
        std::vector<double> row;
        for (const auto &field : fields) {
            row.push_back(field.toDouble());
        }
        data.push_back(row);
    }
    file.close();
}

void saveCSV(const QString &filename, const QStringList &headers, const std::vector<QStringList> &originalData, const std::vector<int> &labels) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << headers.join(',') << "\n";
    for (size_t i = 0; i < originalData.size(); ++i) {
        QStringList line = originalData[i];
        line << QString::number(labels[i]);
        out << line.join(',') << "\n";
    }
    file.close();
}
