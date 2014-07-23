#include "dossier.h"
#include "ui_dossier.h"
#include "mainutprofiler.h"
#include "UTProfiler.h"
#include "QMessageBox"
#include "Inscription.h"
#include "vector"
Dossier::Dossier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dossier)
{
    ui->setupUi(this);
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    ui->uvlabel->hide();
    ui->noteLabel->hide();
    ui->uvsComboBox->hide();
    ui->noteCombo->hide();
    ui->noteLabel->hide();
    ui->ajouterInscription->hide();
    ui->Sauvegarder->hide();

    if(mainUTProfiler.connectDb()){

       QSqlQueryModel *modelFormation= new QSqlQueryModel();
       QSqlQueryModel *modelUvs= new QSqlQueryModel();
       QSqlQueryModel *modelNNotes= new QSqlQueryModel();
       QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

       // SET  "Formations"
         query->prepare("SELECT nom FROM formation");
         if(query->exec()){
            modelFormation->setQuery(*query);
            ui->formationDosierCombo->setModel(modelFormation);
         }


         // SET  "UVS"
           query->prepare("SELECT code FROM UV");
           if(query->exec()){
              modelUvs->setQuery(*query);
              ui->uvsComboBox->setModel(modelUvs);
           }
          // SET "NOTES"
           query->prepare("SELECT noteType FROM note");
           if(query->exec()){
              modelNNotes->setQuery(*query);
              ui->noteCombo->setModel(modelNNotes);
           }


    }
    mainUTProfiler.deconnect();
}

Dossier::~Dossier()
{
    delete ui;
    //delete dossier;
}

void Dossier::on_createDosiier_clicked()
{
    QString dossierIDE = ui->dossierID->text();
    QString formation = ui->formationDosierCombo->currentText();
    int nbSemestres= ui->nbSemestreSpin->value();
    if(dossierIDE.isEmpty() || formation.isEmpty() ){
        QMessageBox::information(this,"Invalid input","no specified IDD or Cursus name");
        return;
    }
     QMessageBox::information(this,"Important","N'oubliez pas de conserver votre IDE de dossier pour le consuler ("+dossierIDE+")");
    this->dossier= new DossierEtudiant(dossierIDE,nbSemestres,formation);
    ui->createDosiier->hide();

    ui->noteLabel->show();
    ui->uvsComboBox->show();
    ui->noteCombo->show();
    ui->noteLabel->show();
    ui->ajouterInscription->show();
    ui->uvlabel->show();
    ui->Sauvegarder->show();

}

void Dossier::on_ajouterInscription_clicked()
{
    QString codeUvToAdd =ui->uvsComboBox->currentText();

    bool final;
    QString cat;
    float probaR;
    QString title;
    int nbCredit;
    Note note;
    UV uv;
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){
       QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

         query->prepare("SELECT * FROM UV WHERE code=:code");
         query->bindValue(0,codeUvToAdd);

        if(query->exec()){
            while(query->next()){
                if(query->value(5).toString()=="OUI")
                    final=true;
                else
                    final=false;
                title=query->value(1).toString();
                cat=query->value(2).toString();
                nbCredit=query->value(3).toInt();
                probaR=query->value(10).toFloat();

                 uv= UV(codeUvToAdd,title,nbCredit,cat,probaR,final);

            }
         }
        else
            qDebug()<<" Failed to execute Query";

    }
    mainUTProfiler.deconnect();


    if(ui->noteCombo->currentText()=="A")
         note=(Note)0;
    else if (ui->noteCombo->currentText()=="B")
        note=(Note)1;
    else if (ui->noteCombo->currentText()=="C")
        note=(Note)2;
    else if (ui->noteCombo->currentText()=="D")
        note=(Note)3;
    else if (ui->noteCombo->currentText()=="E")
        note=(Note)4;
    else if (ui->noteCombo->currentText()=="F")
        note=(Note)5;
    else if (ui->noteCombo->currentText()=="Fx")
        note=(Note)6;
    else if (ui->noteCombo->currentText()=="RESERVE")
        note=(Note)7;
    else if (ui->noteCombo->currentText()=="ABS")
        note=(Note)8;
    else if (ui->noteCombo->currentText()=="EnCours")
        note=(Note)9;

    InscriptionUV nvIns(uv,note);
    // Ajout dans le dossier
    dossier->addInscription(nvIns);
    ui->uvsComboBox->removeItem(ui->uvsComboBox->currentIndex());
    QMessageBox::information(this,"l'Ajout de l'UV",codeUvToAdd+"a bien été ajouté dans votre dossier");
}

void Dossier::on_Sauvegarder_clicked()
{
    int confirmation=QMessageBox::warning(this, tr("Confirmez votre Sauvegarde"),tr("Est ce que vous êtes sure de cette opération?"),
                         QMessageBox::Yes | QMessageBox::Default,
                         QMessageBox::No,
                         QMessageBox::Cancel | QMessageBox::Escape );
    qDebug()<<QMessageBox::Yes;
    if(confirmation== QMessageBox::Yes){
     MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
     if(mainUTProfiler.connectDb()){

         QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

         QString result;
         QString code;
         QString dossierName=this->dossier->getIdentifiant() ;
         QString formation = this->dossier->getFormationName();
         for(int i=0; i<this->dossier->getInscriptions().size();i++){

             query->prepare("INSERT INTO historique VALUES (:ideDossier,:codeH,:resultat,:formation)");

             code=dossier->getInscriptions().at(i).getUV().getCode();
                Note note=dossier->getInscriptions().at(i).getResult();
                if(note==0)
                     result="A";
                else if (note==1)
                    result="B";
                else if (note==2)
                    result="C";
                else if (note==3)
                    result="D";
                else if (note==4)
                    result="E";
                else if (note==5)
                    result="F";
                else if (note==6)
                    result="Fx";
                else if (note==7)
                    result="RESERVE";
                else if (note==8)
                    result="ABS";
                else if (note==9)
                    result="EnCours";

              query->bindValue(0,dossierName);
              query->bindValue(1,code);
              query->bindValue(2,result);
              query->bindValue(3,formation);

              if(query->exec()){
                // QMessageBox::information(this,"Dossier sauvegardé"," Votre dossiezr a bien été sauvegardé, Gardez votre IDD\n pour pourvoir le cnsulter ("+dossierName+")");
              }
              else{
                  //QMessageBox::information(this,"Dossier sauvegardé"," Votre dossiezr a bien été sauvegardé, Gardez votre IDD\n pour pourvoir le cnsulter ("+dossierName+")");

              }
        }

         this->close();
     }

   mainUTProfiler.deconnect();
     }


}
