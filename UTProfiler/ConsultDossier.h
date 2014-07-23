#ifndef CONSULTDOSSIER_H
#define CONSULTDOSSIER_H

#include <QDialog>

namespace Ui {
class ConsultDossier;
}

class ConsultDossier : public QDialog
{
    Q_OBJECT

public:
    explicit ConsultDossier(QWidget *parent = 0);
    ~ConsultDossier();

private slots:
    void on_consulter_clicked();

private:
    Ui::ConsultDossier *ui;
};

#endif // CONSULTDOSSIER_H
