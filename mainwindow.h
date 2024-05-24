#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableView>
#include <QHeaderView>
#include <QPushButton>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSplitter>
#include "mymodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    static QList<QStringList> CartDS;
    static QStringList headders;


private slots:
    void loadCSV(const QString &filePath);
    void onOpenFile();
    void onColumnSelectionChanged();
    void saveTableToFile(const QString &filePath);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButtonDisplayTable_clicked();

    void on_pushButtonCart_clicked();

private:
    Ui::MainWindow *ui;
    QTableView *tableView;
    MyModel *model;
    QGroupBox *columnsGroupBox;
    QStringList headers;
    QList<QCheckBox*> checkBoxes;
    QList<QStringList> data;

    void setupHeaderCheckboxes();
    void updateTable();
    void ContextMenu(const QPoint& pos);
    void addToCart();
};

#endif // MAINWINDOW_H
