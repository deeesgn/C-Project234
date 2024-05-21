#ifndef KMEANS_H
#define KMEANS_H

#include <QVector>

class KMeans
{
public:
    KMeans(int k, int maxIterations = 100);

    void fit(const QVector<QVector<double>>& data);
    QVector<int> predict(const QVector<QVector<double>>& data) const;

private:
    int k;
    int maxIterations;
    QVector<QVector<double>> centroids;

    void initializeCentroids(const QVector<QVector<double>>& data);
    int nearestCentroid(const QVector<double>& point) const;
    void updateCentroids(const QVector<QVector<double>>& data, const QVector<int>& labels);
    double distance(const QVector<double>& point1, const QVector<double>& point2) const;
};

#endif // KMEANS_H
