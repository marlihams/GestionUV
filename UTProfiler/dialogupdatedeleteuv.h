#ifndef DIALOGUPDATEDELETEUV_H
#define DIALOGUPDATEDELETEUV_H

#include <QDialog>
#include <QFileInfo>
#include <QSql>

namespace Ui {
class DialogUpdateDeleteUV;
}

class DialogUpdateDeleteUV : public QDialog
{
    Q_OBJECT

public:
    bool setUVcode();
    explicit DialogUpdateDeleteUV(QWidget *parent = 0);
    ~DialogUpdateDeleteUV();
    Ui::DialogUpdateDeleteUV* getUiUVdEleteUpdate(){
        return ui;

    }

private slots:
    void on_deleteUV_clicked();

    void on_updateUV_clicked();

    void on_categorieComb_currentTextChanged(const QString &arg1);


    void on_trueUpdateUV_clicked();

private:
    Ui::DialogUpdateDeleteUV *ui;
};

#endif // DIALOGUPDATEDELETEUV_H
