#include "data_output.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>

void DataOutput::saveSelectedColumns(const QString &filePath, const QStringList &headers, const QList<QStringList> &data) {
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(nullptr, "Error", "Could not save file");
        return;
    }

    QTextStream stream(&file);

    stream << headers.join(',') << "\n";

    for (const QStringList &row : data) {
        stream << row.join(',') << "\n";
    }
    file.close();
    qDebug() << "File saved successfully at" << filePath;
}
