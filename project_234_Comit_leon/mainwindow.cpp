#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mymodel.h"
#include "norm.h"
#include "kmeans.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QHeaderView>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSplitter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    tableView = new QTableView(this);
    model = new MyModel(this);
    tableView->setModel(model);

    columnsGroupBox = new QGroupBox("Select Columns", this);
    columnsGroupBox->setMinimumWidth(200); // Устанавливаем минимальную ширину

    displayButton = new QPushButton("Display Table", this);

    QVBoxLayout *columnsLayout = new QVBoxLayout;
    columnsLayout->addWidget(columnsGroupBox);
    columnsLayout->addWidget(displayButton);
    columnsLayout->addStretch(); // Добавляем пружину для заполнения оставшегося пространства

    QWidget *columnsWidget = new QWidget(this);
    columnsWidget->setLayout(columnsLayout);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(columnsWidget);
    splitter->addWidget(tableView);
    splitter->setStretchFactor(1, 1); // Устанавливаем пропорции растяжения

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(splitter);
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    connect(displayButton, &QPushButton::clicked, this, &MainWindow::onDisplayTable);

    // Добавим действие в меню "Open"
    QAction *openAction = new QAction("&Open", this);
    openAction->setShortcut(QKeySequence::Open);
    connect(openAction, &QAction::triggered, this, &MainWindow::onOpenFile);

    QMenu *fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openAction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onOpenFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, "Open CSV File", "", "CSV Files (*.csv)");
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

    bool isFirstLine = true;
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(',');

        if (isFirstLine) {
            headers = fields;
            isFirstLine = false;
        } else {
            data.append(fields);
        }
    }

    file.close();

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
        connect(checkBox, &QCheckBox::stateChanged, this, &MainWindow::onColumnSelectionChanged);
    }

    columnsGroupBox->setLayout(layout);
}

void MainWindow::onColumnSelectionChanged()
{
    // Можно обновлять визуализацию или выполнять другие действия при изменении выбора колонок.
}

void MainWindow::onDisplayTable()
{
    updateTable();
    QString outputFilePath = "qt_data_output.csv";
    saveTableToFile(outputFilePath);
    normalizeCSV(outputFilePath, "qt_data_norm_output.csv");
    applyKMeansClustering("qt_data_norm_output.csv", "qt_data_with_clusters.csv");
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

void MainWindow::applyKMeansClustering(const QString &inputFilePath, const QString &outputFilePath)
{
    QFile inputFile(inputFilePath);
    if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open input file for KMeans");
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

    int numClusters = 11; // Количество кластеров, которое вы хотите использовать
    KMeans kmeans(numClusters);

    // Подготовка данных для KMeans
    QVector<QVector<double>> numericData;
    for (const QStringList &row : data) {
        QVector<double> numericRow;
        for (const QString &field : row) {
            bool ok;
            double value = field.toDouble(&ok);
            if (ok) {
                numericRow.append(value);
            } else {
                numericRow.append(0); // Для недопустимых значений добавляем 0
            }
        }
        if (!numericRow.isEmpty()) {
            numericData.append(numericRow);
        }
    }

    kmeans.fit(numericData);
    QVector<int> clusters = kmeans.predict(numericData);

    // Добавление столбца "Clusters"
    headers.append("Clusters");
    for (int i = 0; i < data.size(); ++i) {
        data[i].append(QString::number(clusters[i]));
    }

    // Запись данных с кластерами в
    // Запись данных с кластерами в новый файл
    QFile outputFile(outputFilePath);
    if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open output file for KMeans");
        return;
    }

    QTextStream outputStream(&outputFile);
    outputStream << headers.join(',') << "\n";
    for (const QStringList &row : data) {
        outputStream << row.join(',') << "\n";
    }

    outputFile.close();
}
