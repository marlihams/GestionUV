#include "ConsultDossier.h"
#include "ui_ConsultDossier.h"
#include "mainutprofiler.h"

ConsultDossier::ConsultDossier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConsultDossier)
{
    ui->setupUi(this);
}

ConsultDossier::~ConsultDossier()
{
    delete ui;
}

void ConsultDossier::on_consulter_clicked()
{
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    QString dossierName= ui->dossierName->text();

    if(mainUTProfiler.connectDb()){

       QSqlQueryModel *modelUvsDossier= new QSqlQueryModel();
       QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

         query->prepare("SELECT code,uvCategorie,nbCredits FROM historique JOIN UV  on code=codeH WHERE ideDossier=:ideDossier");
         query->bindValue(0,dossierName);
         if(query->exec()){
            modelUvsDossier->setQuery(*query);
            ui->DossierTableView->setModel(modelUvsDossier);

         }
         else
         {
             qDebug()<<query->lastError().text();
         }

         mainUTProfiler.deconnect();
    }
}
