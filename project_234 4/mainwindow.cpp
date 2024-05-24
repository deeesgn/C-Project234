#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mymodel.h"
#include "norm.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSplitter>
#include <QLineEdit>
#include <QChar>
#include <QMenu>
#include <QStandardItemModel>
#include "cart.h"


QList<QStringList> MainWindow::CartDS;
QStringList MainWindow::headders;


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model = new MyModel(this);
    ui->tableView->setModel(model);

    QString filePath = ":/new/prefix1/menu.csv";
    if (!filePath.isEmpty()) {
        loadCSV(filePath);
        setupHeaderCheckboxes();
    }

    connect(ui->lineEditSearch, &QLineEdit::textChanged, this, &MainWindow::on_lineEdit_textChanged);

    // connect a context menu request with a function ContextMenu
    connect(ui->tableView, &QTableView::customContextMenuRequested, this, &MainWindow::ContextMenu);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFile()
{
    QString filePath = ":/new/prefix1/menu.csv";
    if (!filePath.isEmpty()) {
        loadCSV(filePath);
        setupHeaderCheckboxes();
    }
}

void MainWindow::loadCSV(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file");
        return;
    }

    QTextStream stream(&file);
    headers.clear();
    data.clear();

    bool isFirstLine = true, openBracket = false;
    QString cell = "";
    QStringList row;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(',');

        if (isFirstLine) {
            headers = fields;
            isFirstLine = false;
        } else {
            for (QChar c : line)
            {
                if (c == ',' && !openBracket) {
                    row.append(cell);
                    cell.clear();
                } else if (c == '"' && !openBracket) {
                    openBracket = true;
                } else if (c == '"' && openBracket) {
                    openBracket = false;
                } else {
                    cell += c;
                }
            }
            row.append(cell);
            cell.clear();
            data.append(row);
            row.clear();
        }
    }

    file.close();
    MainWindow::headders = headers;
    model->setModelData(headers, data);
}

void MainWindow::setupHeaderCheckboxes()
{
    QVBoxLayout *layout = new QVBoxLayout;
    qDeleteAll(checkBoxes);
    checkBoxes.clear();

    for (const QString &header : headers) {
        QCheckBox *checkBox = new QCheckBox(header);
        checkBoxes.append(checkBox);
        layout->addWidget(checkBox);
    }

    ui->groupBoxFilters->setLayout(layout);
}

void MainWindow::onColumnSelectionChanged()
{
    // Можно обновлять визуализацию или выполнять другие действия при изменении выбора колонок.
}

void MainWindow::updateTable()
{
    QList<int> selectedColumns;
    for (int i = 0; i < checkBoxes.size(); ++i) {
        if (checkBoxes[i]->isChecked()) {
            selectedColumns.append(i);
        }
    }

    QStringList selectedHeaders;
    QList<QStringList> filteredData;

    for (const auto &row : data) {
        QStringList filteredRow;
        for (int col : selectedColumns) {
            filteredRow.append(row.at(col));
        }
        filteredData.append(filteredRow);
    }

    for (int i : selectedColumns) {
        selectedHeaders.append(headers[i]);
    }

    model->setModelData(selectedHeaders, filteredData);
}

void MainWindow::saveTableToFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not save file");
        return;
    }

    QTextStream stream(&file);

    // Записываем заголовки столбцов
    QStringList selectedHeaders;
    for (int i = 0; i < model->columnCount(); ++i) {
        selectedHeaders.append(model->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
    }
    stream << selectedHeaders.join(',') << "\n";

    // Записываем данные таблицы
    for (int row = 0; row < model->rowCount(); ++row) {
        QStringList rowData;
        for (int col = 0; col < model->columnCount(); ++col) {
            rowData.append(model->data(model->index(row, col), Qt::DisplayRole).toString());
        }
        stream << rowData.join(',') << "\n";
    }

    file.close();
}

void MainWindow::on_lineEdit_textChanged(const QString &text)
{
    // get model from tableView
    QAbstractItemModel* model = ui->tableView->model();
    QString searchTextLower = text.toLower();

    for (int row = 0; row < model->rowCount(); ++row)
    {
        //take indexes of cells
        QModelIndex catIndex = model->index(row, 0);
        QModelIndex itemIndex = model->index(row, 1);

        //take values of cells
        QString category = catIndex.data(Qt::DisplayRole).toString().toLower();
        QString item = itemIndex.data(Qt::DisplayRole).toString().toLower();

        //check if our search is contained in cell values
        bool match = category.contains(searchTextLower) || item.contains(searchTextLower);

        ui->tableView->setRowHidden(row, !match);
    }
}

void MainWindow::on_pushButtonDisplayTable_clicked()
{
    updateTable();
    QString outputFilePath = "qt_data_output.csv";
    saveTableToFile(outputFilePath);
    normalizeCSV(outputFilePath, "qt_data_norm_output.csv");
}

void MainWindow::ContextMenu(const QPoint& pos)
{
    QModelIndex index = ui->tableView->indexAt(pos); //take index from QPoint

    if (index.isValid())
    {
        QMenu contextMenu(this); //Create menu
        QString brand = index.data().toString(); //Take value of cell
        QAction* addToCart = new QAction("Add to cart", this); //Create new action
        contextMenu.addAction(addToCart); //Add action to the menu


        connect(addToCart, &QAction::triggered, this, &MainWindow::addToCart); //connect a click on "Add to Cart" with adding row to the cart

        contextMenu.exec(ui->tableView->viewport()->mapToGlobal(pos)); //show menu
    }
}

void MainWindow::addToCart()
{
    QModelIndex index = ui->tableView->currentIndex();
    int RowID = index.row();

    QStringList row;
    QAbstractItemModel *model = ui->tableView->model();
    for (int c = 0; c < model->columnCount(); ++c)
    {
        QModelIndex ind = model->index(RowID, c);
        QVariant cell = model->data(ind);
        row.append(cell.toString());
    }

    MainWindow::CartDS.append(row);
}





void MainWindow::on_pushButtonCart_clicked()
{
    Cart *cart = new Cart(this);
    cart->show();
}

