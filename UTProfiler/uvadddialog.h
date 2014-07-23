#ifndef UVADDDIALOG_H
#define UVADDDIALOG_H

#include <QDialog>
#include <QFileInfo>
#include <QSql>

namespace Ui {
class UVAddDialog;
}

class UVAddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit UVAddDialog(QWidget *parent = 0);
    ~UVAddDialog();

private slots:
    void on_insertUV_clicked();

    void on_categorieComb_currentIndexChanged(const QString &arg1);

private:
    Ui::UVAddDialog *ui;
};

#endif // UVADDDIALOG_H
