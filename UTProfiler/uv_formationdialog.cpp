#include "uv_formationdialog.h"
#include "ui_uv_formationdialog.h"
#include "mainutprofiler.h"
#include <QMessageBox>

UV_FormationDialog::UV_FormationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UV_FormationDialog)
{

    ui->setupUi(this);


    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();

    if(mainUTProfiler.connectDb()){

       QSqlQueryModel *modelUVS= new QSqlQueryModel();
        QSqlQueryModel *modelFormation= new QSqlQueryModel();
        QSqlQueryModel *modelStatut= new QSqlQueryModel();
        QSqlQueryModel *genieModel  = new QSqlQueryModel();
        QSqlQueryModel *filiereModel = new QSqlQueryModel();

        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

        // SET THE statut OBLIGATION
          query->prepare("SELECT etat FROM statut");
          if(query->exec()){
             modelStatut->setQuery(*query);
             ui->obligationStatutcomboBox->setModel(modelStatut);
          }

          // SET All the Uvs on the Combobox
           query->prepare("SELECT code FROM UV");
           if(query->exec()){
                 modelUVS->setQuery(*query);
                 ui->UvsComboBox->setModel(modelUVS);
           }

        // SET THE GENIE
        query->prepare("SELECT genie FROM nomGenie");
        query->exec();
        genieModel->setQuery(*query);
        ui->genieCombo->setModel(genieModel);




         query->prepare("SELECT filiere FROM nomFiliere");
          if(query->exec()){
                 filiereModel->setQuery(*query);
                 ui->filreCombo->setModel(filiereModel);
             }
         // SET ALL The "formation" names
        query->prepare("SELECT nom FROM FORMATION");
         if(query->exec()){
             modelFormation->setQuery(*query);
             ui->formationComboBox->setModel(modelFormation);
         }




          ui->pcbCombo->setModel(modelStatut);
          ui->psfCombo->setModel(modelStatut);
          QString formation=ui->formationComboBox->currentText();

          if(formation=="Branche" || formation=="Filière"){
              ui->genieCombo->show();
          }
          else{
              ui->genieCombo->hide();
          }
          if(formation=="Filière"){
              ui->filreCombo->show();
              ui->labelFilere->show();
              QString genie = ui->genieCombo->currentText();
              query->prepare("SELECT filiere FROM nomFiliere where genie=:genie");
              query->bindValue(0,genie);
              if(query->exec()){
                  filiereModel->setQuery(*query);
                  ui->filreCombo->setModel(filiereModel);

              }
              else
              {

              }

          }
    }
    else
    {
        qDebug()<<"Failed to open connection..";
    }

    mainUTProfiler.deconnect();
}

UV_FormationDialog::~UV_FormationDialog()
{
    delete ui;
}





void UV_FormationDialog::on_addUVFormation_clicked()
{
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){
        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

        query->prepare("INSERT INTO UVFormation (codeUV ,nomFormation,statutObligation,statutPSF,statutPCB,minSemestreConseille,genie,filiere ) VALUES (:codeUV ,:nomFormation,:statutObligation,:statutPSF,:statutPCB,:minSemestreConseille,:genie,:filiere )");
        query->bindValue(0,ui->UvsComboBox->currentText());
        query->bindValue(1,ui->formationComboBox->currentText());
        query->bindValue(2,ui->obligationStatutcomboBox->currentText());
        query->bindValue(3,ui->genieCombo->currentText());
        query->bindValue(4,ui->filreCombo->currentText());
        query->bindValue(5,ui->pcbCombo->currentText());
        query->bindValue(6,ui->psfCombo->currentText());
        query->bindValue(7,ui->nivConseilSpinBox->value());
        if(query->exec()){


            QMessageBox::information(this,"Ajout réussi","la relation "+ui->UvsComboBox->currentText() +" "+ "a bien été ajouté dans le cursus :"+ ui->formationComboBox->currentText());
        }
        else
        {
            qDebug()<<"Failed";
        }
    }


    mainUTProfiler.deconnect();
}



void UV_FormationDialog::on_genieCombo_currentTextChanged(const QString &arg1)
{
   /* static int k=0;
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(k>0 && mainUTProfiler.connectDb()){
        qDebug()<<"coucocu";
    }
    k++;*/
}

void UV_FormationDialog::on_formationComboBox_currentTextChanged(const QString &arg1)
{
   /* static int k=0;
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(k>0 && mainUTProfiler.connectDb()){
        qDebug()<<"coucocu";
    }
    k++;*/
}

void UV_FormationDialog::on_filreCombo_currentTextChanged(const QString &arg1)
{

}

void UV_FormationDialog::on_fitModel_clicked()
{
   /* MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();

    if(mainUTProfiler.connectDb()){

       QSqlQueryModel *modelUVS= new QSqlQueryModel();
        QSqlQueryModel *modelFormation= new QSqlQueryModel();
        QSqlQueryModel *modelStatut= new QSqlQueryModel();
        QSqlQueryModel *genieModel  = new QSqlQueryModel();
        QSqlQueryModel *filiereModel = new QSqlQueryModel();

        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

        // SET THE statut OBLIGATION
          query->prepare("SELECT etat FROM statut");
          if(query->exec()){
             modelStatut->setQuery(*query);
             ui->obligationStatutcomboBox->setModel(modelStatut);
          }

          // SET All the Uvs on the Combobox
           query->prepare("SELECT code FROM UV");
           if(query->exec()){
                 modelUVS->setQuery(*query);
                 ui->UvsComboBox->setModel(modelUVS);
           }

        // SET THE GENIE
        query->prepare("SELECT genie FROM nomGenie");
        query->exec();
        genieModel->setQuery(*query);
        ui->genieCombo->setModel(genieModel);




         query->prepare("SELECT filiere FROM nomFiliere");
          if(query->exec()){
                 filiereModel->setQuery(*query);
                 ui->filreCombo->setModel(filiereModel);
             }
         // SET ALL The "formation" names
        query->prepare("SELECT nom FROM FORMATION");
         if(query->exec()){
             modelFormation->setQuery(*query);
             ui->formationComboBox->setModel(modelFormation);
         }

          ui->pcbCombo->setModel(modelStatut);
          ui->psfCombo->setModel(modelStatut);
          QString formation=ui->formationComboBox->currentText();

          if(formation=="Branche" || formation=="Filière"){
              ui->genieCombo->show();
          }
          else{
              ui->genieCombo->hide();
          }
          if(formation=="Filière"){
              ui->filreCombo->show();
              ui->labelFilere->show();
              QString genie = ui->genieCombo->currentText();
              query->prepare("SELECT filiere FROM nomFiliere where genie=:genie");
              query->bindValue(0,genie);
              if(query->exec()){
                  filiereModel->setQuery(*query);
                  ui->filreCombo->setModel(filiereModel);

              }
              else
              {

              }

          }
    }
    else
    {
        qDebug()<<"Failed to open connection..";
    }

    mainUTProfiler.deconnect();*/
}
