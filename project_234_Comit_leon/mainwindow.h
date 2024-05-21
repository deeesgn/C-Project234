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

private slots:
    void loadCSV(const QString &filePath);
    void onOpenFile();
    void onDisplayTable();
    void onColumnSelectionChanged();
    void saveTableToFile(const QString &filePath);
    void applyKMeansClustering(const QString &inputFilePath, const QString &outputFilePath);

private:
    Ui::MainWindow *ui;
    QTableView *tableView;
    MyModel *model;
    QVBoxLayout *mainLayout;
    QGroupBox *columnsGroupBox;
    QPushButton *displayButton;
    QStringList headers;
    QList<QCheckBox*> checkBoxes;
    QList<QStringList> data;

    void setupHeaderCheckboxes();
    void updateTable();
};

#endif // MAINWINDOW_H
