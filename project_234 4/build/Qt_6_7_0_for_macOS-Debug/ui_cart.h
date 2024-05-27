/********************************************************************************
** Form generated from reading UI file 'cart.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CART_H
#define UI_CART_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_Cart
{
public:
    QGridLayout *gridLayout;
    QTableView *tableView;
    QPushButton *pushButtonClear;
    QPushButton *pushButtonCheck;

    void setupUi(QDialog *Cart)
    {
        if (Cart->objectName().isEmpty())
            Cart->setObjectName("Cart");
        Cart->resize(399, 369);
        gridLayout = new QGridLayout(Cart);
        gridLayout->setObjectName("gridLayout");
        tableView = new QTableView(Cart);
        tableView->setObjectName("tableView");

        gridLayout->addWidget(tableView, 0, 0, 1, 2);

        pushButtonClear = new QPushButton(Cart);
        pushButtonClear->setObjectName("pushButtonClear");

        gridLayout->addWidget(pushButtonClear, 1, 0, 1, 1);

        pushButtonCheck = new QPushButton(Cart);
        pushButtonCheck->setObjectName("pushButtonCheck");

        gridLayout->addWidget(pushButtonCheck, 1, 1, 1, 1);


        retranslateUi(Cart);

        QMetaObject::connectSlotsByName(Cart);
    } // setupUi

    void retranslateUi(QDialog *Cart)
    {
        Cart->setWindowTitle(QCoreApplication::translate("Cart", "Dialog", nullptr));
        pushButtonClear->setText(QCoreApplication::translate("Cart", "Clear cart", nullptr));
        pushButtonCheck->setText(QCoreApplication::translate("Cart", "Proceed", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Cart: public Ui_Cart {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CART_H
