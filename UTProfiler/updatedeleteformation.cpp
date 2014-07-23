#include "updatedeleteformation.h"
#include "ui_updatedeleteformation.h"
#include "mainutprofiler.h"
#include "QMessageBox"
UpdateDeleteFormation::UpdateDeleteFormation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDeleteFormation)
{
    ui->setupUi(this);

    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){

        QSqlQueryModel *modelFormation= new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

        // SET All the Uvs on the Combobox
        query->prepare("SELECT nom FROM Formation");
        if(query->exec()){
            modelFormation->setQuery(*query);
            ui->FormationcomboBox->setModel(modelFormation);

        }


    }
    else
    {
        qDebug()<<"Failed to open connection..";
    }

    mainUTProfiler.deconnect();
}

UpdateDeleteFormation::~UpdateDeleteFormation()
{
    delete ui;
}



void UpdateDeleteFormation::on_deleteFormation_clicked()
{
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){

        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);
        QSqlQueryModel *modelFormationAfterDeletion;

        QString formationNName= ui->FormationcomboBox->currentText();
        query->prepare("DELETE FROM FORMATION WHERE nom=:nom");
        query->bindValue(0,formationNName);

        int confirmation=QMessageBox::warning(this, tr("Confirmez votre suppresion"),tr("Est ce que vous êtes sure de cette opération?"),
                             QMessageBox::Yes | QMessageBox::Default,
                             QMessageBox::No,
                             QMessageBox::Cancel | QMessageBox::Escape );
        qDebug()<<QMessageBox::Yes;
        if(confirmation== QMessageBox::Yes){

            // vers la suppression
            if(query->exec()){
                ui->msgAfterFormationDeletion->setText("la fomation"+ formationNName + "a été bien supprimée" );
                modelFormationAfterDeletion= new QSqlQueryModel();

                query->prepare("SELECT nom FROM Formation");
                query->exec();
                modelFormationAfterDeletion->setQuery(*query);
                ui->FormationcomboBox->setModel(modelFormationAfterDeletion);
               }
            else
            {
                qDebug()<<"unxpecteD error\n";
            }

        }
        else
            return ;


    }
    else
    {
        qDebug()<<"Failed to open connection..";
    }

    mainUTProfiler.deconnect();

}

void UpdateDeleteFormation::on_upDateFormation_clicked()
{
    int valueForPCB=0,valueForPSF=0;
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();

    if(mainUTProfiler.connectDb()){
        QString formationName= ui->FormationcomboBox->currentText();
        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);
        query->prepare("SELECT * FROM FORMATION WHERE nom=:nom");

        query->bindValue(0,formationName);

        if(query->exec()){
            while(query->next())
            {
               ui->nomFormationLineEdit->setText(query->value(0).toString());
               ui->CreditSspinBox->setValue(query->value(1).toInt());
               ui->CSspinBox->setValue(query->value(2).toInt());
               ui->TMspinBox->setValue(query->value(3).toInt());
               ui->CSTMTotalSpinBox->setValue(query->value(5).toInt());
               ui->TSHspinBox->setValue(query->value(4).toInt());
               ui->SPspinBox->setValue(query->value(6).toInt());
               ui->creditsLibrEspinBox->setValue(query->value(7).toInt());

               valueForPCB=query->value(8).toInt();
               if(valueForPCB){
                   ui->PCBspinBox->show();
                   ui->PCBcheckBox->setChecked(true);
                   ui->PCBspinBox->setValue(valueForPCB);
               }
               else
               {
                   ui->PCBspinBox->hide();
                   ui->PCBcheckBox->setChecked(false);


               }


               valueForPSF=query->value(9).toInt();
               if(valueForPSF){
                   ui->PSFspinBox->show();
                   ui->PSFcheckBox->setChecked(true);
                   ui->PSFspinBox->setValue(valueForPSF);
               }
               else{
                   ui->PSFspinBox->hide();
                    ui->PSFcheckBox->setChecked(false);
               }

               ui->nbColTSHspinBox->setValue(query->value(10).toInt());
               ui->nbLigneTSHspinBox->setValue(query->value(11).toInt());
               ui->nbSemesMaXspinBox->setValue(query->value(12).toInt());
          }

       }
        else{
               qDebug()<<"unxpecteD error\n";
        }

    }

    else
    {
        qDebug()<<"Failed to open Connection...";
    }
    mainUTProfiler.deconnect();
}



void UpdateDeleteFormation::on_trueUpdate_clicked()
{
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    QString nameFormarion;
    if(mainUTProfiler.connectDb()){

        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);
        nameFormarion=ui->FormationcomboBox->currentText();
        query->prepare("UPDATE Formation SET nom=:nom,nbCreditsTotal=:nbCreditsTotal ,nbCS=:nbCS,nbTM=:nbTM ,nbTotalCSTM=:nbTotalCSTM,nbTSH=:nbTSH ,nbSP=:nbSP ,nbCLibrePossibleMax=:nbCLibrePossibleMax ,nbPSB=:nbPSB ,nbPSF=:nbPSF ,nbDifferColTSH=:nbDifferColTSH,nbDifferLigneTSH=:nbDifferLigneTSH ,nbSemestreMaxPossible=:nbSemestreMaxPossible WHERE nom=:nom");

        query->bindValue(0,ui->nomFormationLineEdit->text());
        query->bindValue(1,ui->CreditSspinBox->value());
        query->bindValue(2,ui->CSspinBox->value());
        query->bindValue(3,ui->TMspinBox->value());
        query->bindValue(5,ui->CSTMTotalSpinBox->value());
        query->bindValue(4,ui->TSHspinBox->value());
        query->bindValue(6,ui->SPspinBox->value());
        query->bindValue(7,ui->creditsLibrEspinBox->value());

        if(ui->PCBcheckBox->isChecked())
            query->bindValue(8,ui->PCBspinBox->value());
        else
             query->bindValue(8,0);

        if(ui->PSFcheckBox->isChecked())
            query->bindValue(9,ui->PSFspinBox->value());
        else
            query->bindValue(9,0);

        query->bindValue(10,ui->nbColTSHspinBox->value());
        query->bindValue(11,ui->nbLigneTSHspinBox->value());
        query->bindValue(12,ui->nbSemesMaXspinBox->value());

        query->bindValue(13,nameFormarion);
        if((ui->CSTMTotalSpinBox->value()+ui->TSHspinBox->value()+ui->SPspinBox->value()+ui->creditsLibrEspinBox->value()<ui->CreditSspinBox->value()) ||ui->CSspinBox->value()+ui->TMspinBox->value()> ui->CSTMTotalSpinBox->value()){
            QMessageBox::warning(this,"Modification impossible", "icompatibilité dans le calcul");
            return;
        }
        int confirmation=QMessageBox::warning(this, tr("Veuillez Confirmer Votre Modification de Formation"),tr("Est ce que vous êtes sure de cette opération?"),
                             QMessageBox::Yes | QMessageBox::Default,
                             QMessageBox::No,
                             QMessageBox::Cancel | QMessageBox::Escape );
        if(confirmation== QMessageBox::Yes){

            // vers la suppression
            if(query->exec()){
                qDebug()<<"UPDATED !!";
            }
            else
            {
                qDebug()<<"unexpecteD error NO MODIFICIATION\n";
            }

        }
        else
            return ;

    // UPDATE THE FORMATION NAMES
        query->prepare("SELECT nom FROM FORMATION");
        QSqlQueryModel *modelFormationAfterUpdate = new QSqlQueryModel();
        if(query->exec()){
            modelFormationAfterUpdate->setQuery(*query);
            ui->FormationcomboBox->setModel(modelFormationAfterUpdate);
        }
    }
    else
    {
        qDebug()<<"Failed to open connection..";
    }

    mainUTProfiler.deconnect();

}

void UpdateDeleteFormation::on_PCBcheckBox_toggled(bool checked)
{
    if(!checked){
        ui->PCBspinBox->hide();
    }
    else
        ui->PCBspinBox->show();
}

void UpdateDeleteFormation::on_PSFcheckBox_toggled(bool checked)
{
   if(!checked){
        ui->PSFspinBox->hide();
    }
    else
        ui->PSFspinBox->show();
}
