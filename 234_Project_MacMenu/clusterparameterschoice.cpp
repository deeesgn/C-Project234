#include "clusterparameterschoice.h"
#include "ui_clusterparameterschoice.h"

ClusterParametersChoice::ClusterParametersChoice(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ClusterParametersChoice)
{
    ui->setupUi(this);
}

ClusterParametersChoice::~ClusterParametersChoice()
{
    delete ui;
}

void ClusterParametersChoice::on_OK_button_clicked()
{

}

