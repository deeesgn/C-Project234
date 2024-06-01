/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTableView *tableView;
    QLineEdit *lineEditSearch;
    QLabel *label;
    QPushButton *pushButtonDisplayTable;
    QPushButton *pushButtonCart;
    QGroupBox *groupBoxFilters;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName("actionOpen");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tableView = new QTableView(centralwidget);
        tableView->setObjectName("tableView");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setMinimumSize(QSize(550, 0));

        gridLayout->addWidget(tableView, 0, 2, 6, 1);

        lineEditSearch = new QLineEdit(centralwidget);
        lineEditSearch->setObjectName("lineEditSearch");

        gridLayout->addWidget(lineEditSearch, 5, 1, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        label->setFont(font);

        gridLayout->addWidget(label, 5, 0, 1, 1);

        pushButtonDisplayTable = new QPushButton(centralwidget);
        pushButtonDisplayTable->setObjectName("pushButtonDisplayTable");

        gridLayout->addWidget(pushButtonDisplayTable, 4, 0, 1, 2);

        pushButtonCart = new QPushButton(centralwidget);
        pushButtonCart->setObjectName("pushButtonCart");

        gridLayout->addWidget(pushButtonCart, 3, 0, 1, 2);

        groupBoxFilters = new QGroupBox(centralwidget);
        groupBoxFilters->setObjectName("groupBoxFilters");

        gridLayout->addWidget(groupBoxFilters, 0, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actionOpen->setText(QCoreApplication::translate("MainWindow", "&Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        label->setText(QCoreApplication::translate("MainWindow", "Search:", nullptr));
        pushButtonDisplayTable->setText(QCoreApplication::translate("MainWindow", "Display table", nullptr));
        pushButtonCart->setText(QCoreApplication::translate("MainWindow", "Cart", nullptr));
        groupBoxFilters->setTitle(QCoreApplication::translate("MainWindow", "Choose fields to show", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
