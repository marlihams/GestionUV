#include "ViewFormationTable.h"
#include "ui_ViewFormationTable.h"
#include "mainutprofiler.h"

ViewFormationTable::ViewFormationTable(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ViewFormationTable)
{
    ui->setupUi(this);
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){
       QSqlQueryModel *modelFormation= new QSqlQueryModel();
       QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

       // GET UVs
         query->prepare("SELECT * FROM formation");
         if(query->exec()){
            modelFormation->setQuery(*query);
            ui->tableView->setModel(modelFormation);
         }


    }
    mainUTProfiler.deconnect();

}

ViewFormationTable::~ViewFormationTable()
{
    delete ui;
}
