#ifndef UV_FORMATIONDIALOG_H
#define UV_FORMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class UV_FormationDialog;
}

class UV_FormationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UV_FormationDialog(QWidget *parent = 0);
    ~UV_FormationDialog();

private slots:


    void on_addUVFormation_clicked();


    void on_genieCombo_currentTextChanged(const QString &arg1);

    void on_formationComboBox_currentTextChanged(const QString &arg1);

    void on_filreCombo_currentTextChanged(const QString &arg1);

    void on_fitModel_clicked();

private:
    Ui::UV_FormationDialog *ui;
};

#endif // UV_FORMATIONDIALOG_H
