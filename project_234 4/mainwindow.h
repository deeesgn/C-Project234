#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QStringList>
#include <QCheckBox>

namespace Ui {
class MainWindow;
}

class MyModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static QList<QStringList> CartDS;
    static QStringList headders;

private slots:
    void onOpenFile();
    void on_pushButtonDisplayTable_clicked();
    void on_pushButtonCart_clicked();
    void on_lineEdit_textChanged(const QString &text);

private:
    Ui::MainWindow *ui;
    MyModel *model;
    QStringList headers;
    QList<QStringList> data;
    QList<QCheckBox*> checkBoxes;

    void loadCSVForTable(const QString &filePath);
    void loadCSV(const QString &filePath, std::vector<std::vector<double>> &data, std::vector<QStringList> &originalData); // Изменено
    void setupHeaderCheckboxes();
    void onColumnSelectionChanged();
    void updateTable();
    void saveTableToFile(const QString &filePath);
    void ContextMenu(const QPoint& pos);
    void addToCart();
};

#endif // MAINWINDOW_H
