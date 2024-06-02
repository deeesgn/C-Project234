#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include <QString>
#include <QStringList>

class KMeans {
public:
    KMeans(int k, int maxIterations = 100);
    void fit(const std::vector<std::vector<double>> &data);
    std::vector<int> predict(const std::vector<std::vector<double>> &data);
    std::vector<std::vector<double>> getCentroids();

private:
    void initialization(const std::vector<std::vector<double>> &data);
    int nearest(const std::vector<double> &point);
    std::vector<double> compute(const std::vector<std::vector<double>> &cluster);

    int k;
    int maxIterations;
    std::vector<std::vector<double>> centroids;
};

void loadCSV(const QString &filename, std::vector<std::vector<double>> &data, std::vector<QStringList> &originalData);
void saveCSV(const QString &filename, const QStringList &headers, const std::vector<QStringList> &originalData, const std::vector<int> &labels);

#endif // KMEANS_H
