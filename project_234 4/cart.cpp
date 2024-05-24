#include "cart.h"
#include "ui_cart.h"
#include <QStandardItemModel>
#include <QMessageBox>


Cart::Cart(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Cart)
{
    ui->setupUi(this);

    QStandardItemModel *model = new QStandardItemModel(this);

    int i = 0;
    for (QString head : MainWindow::headders)
    {
        QStandardItem *item = new QStandardItem(head);
        model->setHorizontalHeaderItem(i, item);
        i++;
    }
    for (int i = 0; i < MainWindow::CartDS.length(); ++i)
    {
        for (int j = 0; j < MainWindow::CartDS[0].length(); ++j) {
            QStandardItem *item = new QStandardItem(MainWindow::CartDS[i][j]);
            model->setItem(i, j, item);
        }
    }

    ui->tableView->setModel(model);
}

Cart::~Cart()
{
    delete ui;
}

void Cart::on_pushButtonClear_clicked()
{
    MainWindow::CartDS.clear();
    QStandardItemModel *model = new QStandardItemModel(this);

    int i = 0;
    for (QString head : MainWindow::headders)
    {
        QStandardItem *item = new QStandardItem(head);
        model->setHorizontalHeaderItem(i, item);
        i++;
    }
    for (int i = 0; i < MainWindow::CartDS.length(); ++i)
    {
        for (int j = 0; j < MainWindow::CartDS[0].length(); ++j) {
            QStandardItem *item = new QStandardItem(MainWindow::CartDS[i][j]);
            model->setItem(i, j, item);
        }
    }

    ui->tableView->setModel(model);
}


void Cart::on_pushButtonCheck_clicked()
{
    QMessageBox::information(this, "", "Enjoy your meal!");
}

