#ifndef DATA_OUTPUT_H
#define DATA_OUTPUT_H

#include <QString>
#include <QStringList>
#include <QList>

class DataOutput {
public:
    static void saveSelectedColumns(const QString &filePath, const QStringList &headers, const QList<QStringList> &data);
};

#endif // DATA_OUTPUT_H
