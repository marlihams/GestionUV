#ifndef UPDATEDELETEFORMATION_H
#define UPDATEDELETEFORMATION_H

#include <QDialog>

namespace Ui {
class UpdateDeleteFormation;
}

class UpdateDeleteFormation : public QDialog
{
    Q_OBJECT

public:
    explicit UpdateDeleteFormation(QWidget *parent = 0);
    ~UpdateDeleteFormation();

private slots:
    void on_deleteFormation_clicked();

    void on_upDateFormation_clicked();

    void on_trueUpdate_clicked();

    void on_PCBcheckBox_toggled(bool checked);

    void on_PSFcheckBox_toggled(bool checked);

private:
    Ui::UpdateDeleteFormation *ui;
};

#endif // UPDATEDELETEFORMATION_H
