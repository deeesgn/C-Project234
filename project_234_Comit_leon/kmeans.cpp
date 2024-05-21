#include "kmeans.h"
#include <QtMath>
#include <QRandomGenerator>

KMeans::KMeans(int k, int maxIterations)
    : k(k), maxIterations(maxIterations)
{
}

void KMeans::fit(const QVector<QVector<double>>& data)
{
    int numPoints = data.size();
    QVector<int> labels(numPoints, -1);

    initializeCentroids(data);

    for (int iter = 0; iter < maxIterations; ++iter) {
        bool changed = false;

        // Assign each point to the nearest centroid
        for (int i = 0; i < numPoints; ++i) {
            int newLabel = nearestCentroid(data[i]);
            if (labels[i] != newLabel) {
                labels[i] = newLabel;
                changed = true;
            }
        }

        if (!changed) break;

        // Update centroids based on the assignments
        updateCentroids(data, labels);
    }
}

QVector<int> KMeans::predict(const QVector<QVector<double>>& data) const
{
    QVector<int> labels(data.size());

    for (int i = 0; i < data.size(); ++i) {
        labels[i] = nearestCentroid(data[i]);
    }

    return labels;
}

void KMeans::initializeCentroids(const QVector<QVector<double>>& data)
{
    int numPoints = data.size();
    QVector<int> usedIndices;

    centroids.clear();
    for (int i = 0; i < k; ++i) {
        int index;
        do {
            index = QRandomGenerator::global()->bounded(numPoints);
        } while (usedIndices.contains(index));
        usedIndices.append(index);
        centroids.append(data[index]);
    }
}

int KMeans::nearestCentroid(const QVector<double>& point) const
{
    int nearestIndex = 0;
    double minDistance = distance(point, centroids[0]);

    for (int i = 1; i < k; ++i) {
        double d = distance(point, centroids[i]);
        if (d < minDistance) {
            minDistance = d;
            nearestIndex = i;
        }
    }

    return nearestIndex;
}

void KMeans::updateCentroids(const QVector<QVector<double>>& data, const QVector<int>& labels)
{
    QVector<int> counts(k, 0);
    QVector<QVector<double>> newCentroids(k, QVector<double>(data[0].size(), 0.0));

    for (int i = 0; i < data.size(); ++i) {
        int label = labels[i];
        counts[label]++;
        for (int j = 0; j < data[i].size(); ++j) {
            newCentroids[label][j] += data[i][j];
        }
    }

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < newCentroids[i].size(); ++j) {
            if (counts[i] != 0) {
                newCentroids[i][j] /= counts[i];
            }
        }
    }

    centroids = newCentroids;
}

double KMeans::distance(const QVector<double>& point1, const QVector<double>& point2) const
{
    double sum = 0.0;
    for (int i = 0; i < point1.size(); ++i) {
        sum += qPow(point1[i] - point2[i], 2);
    }
    return qSqrt(sum);
}
