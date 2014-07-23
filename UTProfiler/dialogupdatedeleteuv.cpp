#include "dialogupdatedeleteuv.h"
#include "ui_dialogupdatedeleteuv.h"
#include "mainutprofiler.h"
#include <QMessageBox>

DialogUpdateDeleteUV::DialogUpdateDeleteUV(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogUpdateDeleteUV)
{
    ui->setupUi(this);

    ui->tshTypeCombo->hide();
    ui->tshLabelType_2->hide();
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){

        QSqlQueryModel *modelUvs= new QSqlQueryModel();
        QSqlQueryModel *modelCategorie= new QSqlQueryModel();
        QSqlQueryModel *modelSaison= new QSqlQueryModel();
        QSqlQueryModel *modelStatus = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

        // SET All the Uvs on the Combobox
        query->prepare("SELECT code FROM UV");
        if(query->exec()){
            modelUvs->setQuery(*query);
            ui->uvsModelCombo->setModel(modelUvs);

        }

        // SET The Possible Categorie Values
        query->prepare("SELECT uvType FROM categorie");
        query->exec();
        modelCategorie->setQuery(*query);
        ui->categorieComb->setModel(modelCategorie);

        // SET The Possible Saison Values

        query->prepare("SELECT SaisonType FROM saison");
        query->exec();
        modelSaison->setQuery(*query);
        ui->saisonComb->setModel(modelSaison);

        // SET THE STATUS OUI OR NO
        query->prepare("SELECT etat FROM statut");
        query->exec();
        modelStatus->setQuery(*query);
        ui->statutFinalCombo_2->setModel(modelStatus);
        ui->statutMedianCombo_2->setModel(modelStatus);
        ui->statutProjCombo_2->setModel(modelStatus);
        ui->statutTpComb_2->setModel(modelStatus);
        ui->statutTDCombo_2->setModel(modelStatus);

        // SET tHE HIDEN TSH types
        query->prepare("SELECT * FROM TSH");
        query->exec();
        QSqlQueryModel *modelTypeTsh = new QSqlQueryModel();
        modelTypeTsh->setQuery(*query);
        ui->tshTypeCombo->setModel(modelTypeTsh);
        // Disconnection

    }
    else
    {
        qDebug()<<"Failed to open connection..";
    }

    mainUTProfiler.deconnect();


}



DialogUpdateDeleteUV::~DialogUpdateDeleteUV()
{
    delete ui;
}

void DialogUpdateDeleteUV::on_deleteUV_clicked()
{
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){

        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);
        QSqlQueryModel *modelUvs;

        QString uvCode= ui->uvsModelCombo->currentText();
        query->prepare("DELETE FROM UV WHERE code=:code");
        query->bindValue(0,uvCode);

        int confirmation=QMessageBox::warning(this, tr("Confirmez votre suppresion"),tr("Est ce que vous êtes sure de cette opération?"),
                             QMessageBox::Yes | QMessageBox::Default,
                             QMessageBox::No,
                             QMessageBox::Cancel | QMessageBox::Escape );
        qDebug()<<QMessageBox::Yes;
        if(confirmation== QMessageBox::Yes){

            // vers la suppression
            if(query->exec()){
                ui->msgAfterDeletion->setText("l'UV"+ uvCode + "a été bien supprimée" );
                modelUvs= new QSqlQueryModel();

                query->prepare("SELECT code FROM UV");
                query->exec();
                modelUvs->setQuery(*query);
                ui->uvsModelCombo->setModel(modelUvs);
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

void DialogUpdateDeleteUV::on_updateUV_clicked()
{
    QString typeTSH,statut,catToset,saisonToset, description;
    int index;


    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();

    if(mainUTProfiler.connectDb()){
        QString uvCode= ui->uvsModelCombo->currentText();
        ui->msgAfterDeletion->setText(uvCode);
        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);
        query->prepare("SELECT * FROM UV WHERE code=:code");

        query->bindValue(0,uvCode);

        if(query->exec()){
            while(query->next())
            {
               ui->codeLine->setText(query->value(0).toString());
               ui->titreLine->setText(query->value(1).toString());

               catToset =QString(query->value(2).toString());
               index = ui->categorieComb->findText(catToset);
               ui->categorieComb->setCurrentIndex(index);
               if(catToset=="TSH"){
                   ui->tshTypeCombo->show();
                   ui->tshLabelType_2->show();

                    typeTSH = QString(query->value(12).toString());
                    index = ui->tshTypeCombo->findText(typeTSH);
                    ui->tshTypeCombo->setCurrentIndex(index);
               }
               else
               {

                   ui->tshTypeCombo->hide();
                   ui->tshLabelType_2->hide();
                   ui->tshTypeCombo->setCurrentIndex(0);
               }

               ui->nbCreditspinBox->setValue(query->value(3).toInt());
               // SET SAISON
               saisonToset=QString (query->value(4).toString());
               index = ui->saisonComb->findText(saisonToset);
               ui->saisonComb->setCurrentIndex(index);

               // Statut final
               statut = QString(query->value(5).toString());
               index=ui->statutFinalCombo_2->findText(statut);
               ui->statutFinalCombo_2->setCurrentIndex(index);

               // Statut Median
               statut = QString(query->value(6).toString());
               index=ui->statutMedianCombo_2->findText(statut);
               ui->statutMedianCombo_2->setCurrentIndex(index);

               // Statut Project
               statut = QString(query->value(7).toString());
               index=ui->statutProjCombo_2->findText(statut);
               ui->statutProjCombo_2->setCurrentIndex(index);

               // SET TD
               statut = QString(query->value(8).toString());
               index=ui->statutTDCombo_2->findText(statut);
               ui->statutTDCombo_2->setCurrentIndex(index);

               //SET TP
               statut = QString(query->value(9).toString());
               index=ui->statutTpComb_2->findText(statut);
               ui->statutTpComb_2->setCurrentIndex(index);

               // SET THE Proba of Sucess
               ui->probaReussiteUV_2->setValue(query->value(10).toFloat());

               // SET THE DESCRIPION
               description = QString(query->value(11).toString());
               ui->description->setPlainText(description);
            }
        }
        else
        {
            qDebug()<<"FAILED TO SELECTED THE WANTED UV";
        }

    }
    else
    {
        qDebug()<<"Failed to open Connection...";
    }
    mainUTProfiler.deconnect();
}

void DialogUpdateDeleteUV::on_categorieComb_currentTextChanged(const QString &arg1)
{
    QString categorie= ui->categorieComb->currentText();



    if (categorie=="TSH")
    {
            ui->tshTypeCombo->show();
            ui->tshLabelType_2->show();

    }
    else
    {
        ui->tshTypeCombo->hide();
        ui->tshLabelType_2->hide();
    }
}



void DialogUpdateDeleteUV::on_trueUpdateUV_clicked()
{
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){

        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);


   query->prepare("UPDATE UV SET code=:code, titre=:titre,uvCategorie=:uvCategorie,nbCredits=:nbCredits,saison=:saison,final=:final,median=:median,projet=:projet,td=:td,tp=:tp,tauxDeReussiteRecent=:tauxDeReussiteRecent,description=:description,typeTSH=:typeTSH WHERE code=:code");
        query->bindValue(0,ui->codeLine->text());
        query->bindValue(1,ui->titreLine->text());
        query->bindValue(2,ui->categorieComb->currentText());
        query->bindValue(3,ui->nbCreditspinBox->value());
        query->bindValue(4,ui->saisonComb->currentText());
        query->bindValue(5,ui->statutFinalCombo_2->currentText());
        query->bindValue(6,ui->statutMedianCombo_2->currentText());
        query->bindValue(7,ui->statutProjCombo_2->currentText());
        query->bindValue(8,ui->statutTDCombo_2->currentText());
        query->bindValue(9,ui->statutTpComb_2->currentText());
        query->bindValue(10,ui->probaReussiteUV_2->value());
        query->bindValue(11,ui->description->toPlainText());
        query->bindValue(13,ui->uvsModelCombo->currentText());
        if(ui->categorieComb->currentText()=="TSH")
            query->bindValue(12,ui->tshTypeCombo->currentText());
        else
             query->bindValue(12,NULL);


        int confirmation=QMessageBox::warning(this, tr("Veuillez Confirmer Votre Modification"),tr("Est ce que vous êtes sure de cette opération?"),
                             QMessageBox::Yes | QMessageBox::Default,
                             QMessageBox::No,
                             QMessageBox::Cancel | QMessageBox::Escape );
        if(confirmation== QMessageBox::Yes){

            if(query->exec()){
                ui->msgAfterDeletion->setText("l'UV a bien été modifiée" );

                QSqlQueryModel *modelUvs= new QSqlQueryModel();
                QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

                // SET All the Uvs on the Combobox
                query->prepare("SELECT code FROM UV");
                if(query->exec()){
                    modelUvs->setQuery(*query);
                    ui->uvsModelCombo->setModel(modelUvs);

                }
            }
            else
            {
                qDebug()<<"unxpecteD error NO MODIFICIATION\n";
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
