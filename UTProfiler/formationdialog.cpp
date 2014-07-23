#include "formationdialog.h"
#include "ui_formationdialog.h"
#include "mainutprofiler.h"
#include <QMessageBox>
FormationDialog::FormationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormationDialog)
{
    ui->setupUi(this);
    ui->PCBspinBox->hide();
    ui->PSFspinBox->hide();

}

FormationDialog::~FormationDialog()
{
    delete ui;
}



void FormationDialog::on_PCBcheckBox_toggled(bool checked)
{

    if(!checked){
        ui->PCBspinBox->hide();
    }
    else
        ui->PCBspinBox->show();
}

void FormationDialog::on_PSFcheckBox_toggled(bool checked)
{
    if(!checked){
        ui->PSFspinBox->hide();
    }
    else
        ui->PSFspinBox->show();
}

void FormationDialog::on_addFormation_clicked()
{

    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    QSqlQuery *query;
    if(mainUTProfiler.connectDb()){
        query=  new QSqlQuery();
        query->prepare("INSERT INTO FORMATION (nom,nbCreditsTotal ,nbCS,nbTM ,nbTotalCSTM,nbTSH ,nbSP ,nbCLibrePossibleMax ,nbPSB ,nbPSF ,nbDifferColTSH,nbDifferLigneTSH ,nbSemestreMaxPossible )"
                       "VALUES (:nom,:nbCreditsTotal ,:nbCS,:nbTM ,:nbTotalCSTM,:nbTSH ,:nbSP ,:nbCLibrePossibleMax ,:nbPSB ,:nbPSF ,:nbDifferColTSH,:nbDifferLigneTSH ,:nbSemestreMaxPossible )");
        if(!ui->nomFormationLineEdit->text().isEmpty())
            query->bindValue(0,ui->nomFormationLineEdit->text());
        else
        {
            QMessageBox::information(this,"Invalid input","Le nom de la formation est nulle");
            return;
        }
        query->bindValue(1,ui->CreditSspinBox->value());
        query->bindValue(2,ui->CSspinBox->value());
        query->bindValue(3,ui->TMspinBox->value());
        query->bindValue(5,ui->TSHspinBox->value());
        query->bindValue(4,ui->CSTMTotalSpinBox->value());
        query->bindValue(6,ui->SPspinBox->value());
        query->bindValue(7,ui->creditsLibrEspinBox->value());
        // IN the end if no PSB or PCB have been given we will insert 0 instead of NULL
        query->bindValue(8,ui->PCBspinBox->value());
        query->bindValue(9,ui->PSFspinBox->value());
        query->bindValue(10,ui->nbColTSHspinBox->value());
        query->bindValue(11,ui->nbLigneTSHspinBox->value());
        query->bindValue(12,ui->nbSemesMaXspinBox->value());

        if((ui->CSTMTotalSpinBox->value()+ui->TSHspinBox->value()+ui->SPspinBox->value()+ui->creditsLibrEspinBox->value()<ui->CreditSspinBox->value()) ||ui->CSspinBox->value()+ui->TMspinBox->value()> ui->CSTMTotalSpinBox->value()){
            QMessageBox::information(this,"Invalid Input", "icompatibilité dans le calcul");
          return;
        }
        if(query->exec()){
            QMessageBox::information(this,"Success", ui->nomFormationLineEdit->text() + " a été bien ajoutée");
        }
    }
    else
    {
        qDebug()<<"Failed to Connect to Data Base";
    }


}
