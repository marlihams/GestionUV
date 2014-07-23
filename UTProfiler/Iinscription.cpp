#include "Inscription.h"
#include "ui_Inscription.h"
#include "mainutprofiler.h"


Inscription::Inscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Inscription)
{
    ui->setupUi(this);
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();

    if(mainUTProfiler.connectDb()){

       QSqlQueryModel *modelUvs= new QSqlQueryModel();
       QSqlQueryModel *modelNNotes= new QSqlQueryModel();
       QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

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
         else
             qDebug()<<"failed to load formations";
    }
    mainUTProfiler.deconnect();
}

Inscription::~Inscription()
{
    delete ui;
}
