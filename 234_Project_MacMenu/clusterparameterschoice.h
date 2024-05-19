#ifndef CLUSTERPARAMETERSCHOICE_H
#define CLUSTERPARAMETERSCHOICE_H

#include <QDialog>

namespace Ui {
class ClusterParametersChoice;
}

class ClusterParametersChoice : public QDialog
{
    Q_OBJECT

public:
    explicit ClusterParametersChoice(QWidget *parent = nullptr);
    ~ClusterParametersChoice();

private:
    Ui::ClusterParametersChoice *ui;
};

#endif // CLUSTERPARAMETERSCHOICE_H
