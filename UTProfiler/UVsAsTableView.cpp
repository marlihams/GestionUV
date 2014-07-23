#include "UVsAsTableView.h"
#include "ui_UVsAsTableView.h"
#include "mainutprofiler.h"

UVsAsTableView::UVsAsTableView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UVsAsTableView)
{
    ui->setupUi(this);
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){
       QSqlQueryModel *modelUvs= new QSqlQueryModel();
       QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

       // GET UVs
         query->prepare("SELECT * FROM UV");
         if(query->exec()){
            modelUvs->setQuery(*query);
            ui->tableView->setModel(modelUvs);
         }


    }
    mainUTProfiler.deconnect();

}

UVsAsTableView::~UVsAsTableView()
{
    delete ui;
}
