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
    int k;
    int maxIterations;
    std::vector<std::vector<double>> centroids;

    void initialization(const std::vector<std::vector<double>> &data);
    int nearest(const std::vector<double> &point);
    std::vector<double> compute(const std::vector<std::vector<double>> &cluster);};

void loadCSV(const QString &filename, std::vector<std::vector<double>> &data);
void saveCSV(const QString &filename, const QStringList &headers, const std::vector<std::vector<double>> &data, const std::vector<int> &clusters);

#endif // KMEANS_H
