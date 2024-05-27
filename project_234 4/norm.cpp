#include "norm.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

void normalizeCSV(const QString &inputFilePath, const QString &outputFilePath)
{
    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Could not open input file" << inputFilePath;
        return;
    }

    QStringList headers;
    QList<QStringList> data;

    QTextStream inputStream(&inputFile);
    bool isFirstLine = true;

    while (!inputStream.atEnd()) {
        QString line = inputStream.readLine();
        QStringList fields = line.split(',');

        if (isFirstLine) {
            headers = fields;
            isFirstLine = false;
        } else {
            data.append(fields);
        }
    }
    inputFile.close();

    // Нормализация данных
    int numColumns = headers.size();
    QList<double> minValues(numColumns, std::numeric_limits<double>::max());
    QList<double> maxValues(numColumns, std::numeric_limits<double>::lowest());

    // Поиск минимальных и максимальных значений для каждого столбца
    for (const QStringList &row : data) {
        for (int i = 0; i < numColumns; ++i) {
            bool ok;
            double value = row[i].toDouble(&ok);
            if (ok) {
                if (value < minValues[i]) minValues[i] = value;
                if (value > maxValues[i]) maxValues[i] = value;
            }
        }
    }

    // Применение нормализации
    QList<QStringList> normalizedData;
    for (const QStringList &row : data) {
        QStringList normalizedRow;
        for (int i = 0; i < numColumns; ++i) {
            bool ok;
            double value = row[i].toDouble(&ok);
            if (ok) {
                double minValue = minValues[i];
                double maxValue = maxValues[i];
                double normalizedValue = (value - minValue) / (maxValue - minValue);
                normalizedRow.append(QString::number(normalizedValue));
            } else {
                normalizedRow.append(row[i]);
            }
        }
        normalizedData.append(normalizedRow);
    }

    // Запись нормализованных данных в новый файл
    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Could not open output file" << outputFilePath;
        return;
    }

    QTextStream outputStream(&outputFile);
    outputStream << headers.join(',') << "\n";
    for (const QStringList &row : normalizedData) {
        outputStream << row.join(',') << "\n";
    }

    outputFile.close();
}
