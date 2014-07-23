#ifndef DOSSIER_H
#define DOSSIER_H

#include <QDialog>
#include "UTProfiler.h"
#include "Inscription.h"
namespace Ui {
class Dossier;
}

class Dossier : public QDialog
{
    Q_OBJECT

public:
    explicit Dossier(QWidget *parent = 0);
    ~Dossier();

private slots:
    void on_createDosiier_clicked();

    void on_ajouterInscription_clicked();

    void on_Sauvegarder_clicked();

private:
    Ui::Dossier *ui;
  DossierEtudiant *dossier;

};

#endif // DOSSIER_H
