#ifndef FORMATIONDIALOG_H
#define FORMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class FormationDialog;
}

class FormationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormationDialog(QWidget *parent = 0);
    ~FormationDialog();


private slots:



    void on_PCBcheckBox_toggled(bool checked);

    void on_PSFcheckBox_toggled(bool checked);

    void on_addFormation_clicked();

private:
    Ui::FormationDialog *ui;
};

#endif // FORMATIONDIALOG_H
