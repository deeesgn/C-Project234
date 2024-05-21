#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QStringList>
#include <QList>

class MyModel : public QAbstractTableModel
{
    Q_OBJECT

public:  // Изменить на public
    MyModel(QObject *parent = nullptr);

    void setModelData(const QStringList &headers, const QList<QStringList> &rows);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QStringList m_headers;
    QList<QStringList> m_data;
};

#endif // MYMODEL_H
