#include "uvadddialog.h"
#include "ui_uvadddialog.h"
#include "mainutprofiler.h"


const int MAXCREDIT=6;

UVAddDialog::UVAddDialog(QWidget *parent) :QDialog(parent),ui(new Ui::UVAddDialog)
{
    ui->setupUi(this);

    ui->tshTypeCombo->hide();
    ui->tshLabelType->hide();

    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    if(mainUTProfiler.connectDb()){
        ui->test->setText("Still Connected ...");

        QSqlQueryModel *modelCategorie= new QSqlQueryModel();
        QSqlQueryModel *modelSaison= new QSqlQueryModel();
        QSqlQueryModel *modelStatus = new QSqlQueryModel();
        QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

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

        // SET ALL The Status VALUES (OUI OR NON )
        query->prepare("SELECT etat FROM statut");
        query->exec();
        modelStatus->setQuery(*query);
        ui->statutFinalCombo->setModel(modelStatus);
        ui->statutMedianCombo->setModel(modelStatus);
        ui->statutProjCombo->setModel(modelStatus);
        ui->statutTpComb->setModel(modelStatus);
        ui->statutTDCombo->setModel(modelStatus);
        // Disconnection

    }
    else
        ui->test->setText("Failed ... ");

    mainUTProfiler.deconnect();


}

UVAddDialog::~UVAddDialog()
{
    delete ui;
}

void UVAddDialog::on_insertUV_clicked()
{
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();
    QString code,titre,categorie,saison;
    int nbCredit;

    code=  ui->codeLine->text();
    titre= ui->titreLine->text();
    categorie= ui->categorieComb->currentText();
    saison= ui->saisonComb->currentText();
    nbCredit = ui->nbCreditspinBox->value();

    mainUTProfiler.deconnect();
    if(!mainUTProfiler.connectDb() || code.isEmpty() || titre.isEmpty() ){

            qDebug()<<"Insertion Failed";
            return;
    }
    QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb);

    query->prepare("INSERT INTO UV (code,titre,uvCategorie,nbCredits,saison,final,median,projet,td,tp,tauxDeReussiteRecent,description,typeTSH)"
                   "VALUES (:code,:titre,:uvCategorie,:nbCredits,:saison,:final,:median,:projet,:td,:tp,:tauxDeReussiteRecent,:description,:typeTSH)");

    query->bindValue(0,code);
    query->bindValue(1,titre);
    query->bindValue(2,categorie);
    query->bindValue(3,nbCredit);
    query->bindValue(4,saison);
    query->bindValue(5,ui->statutFinalCombo->currentText());
    query->bindValue(6,ui->statutMedianCombo->currentText());
    query->bindValue(7,ui->statutProjCombo->currentText());
    query->bindValue(8,ui->statutTDCombo->currentText());
    query->bindValue(9,ui->statutTpComb->currentText());
    query->bindValue(10,ui->probaReussiteUV->value());
    query->bindValue(11,ui->description->toPlainText());
    query->bindValue(12,ui->tshTypeCombo->currentText());

     if(query->exec()){
        ui->test->setText(code +" " + " added !");
    }
     else
     {
         ui->test->setText("Failed...");

     }

    mainUTProfiler.disconnect();
}

void UVAddDialog::on_categorieComb_currentIndexChanged(const QString &arg1)
{
    QString categorie= ui->categorieComb->currentText();
    MainUTProfiler &mainUTProfiler=MainUTProfiler::getUTProfiler();



    if (categorie=="TSH")
    {
        if(mainUTProfiler.connectDb())
        {
            QSqlQuery *query = new QSqlQuery(mainUTProfiler.mydb) ;
            query->prepare("SELECT * FROM TSH");
            query->exec();
            QSqlQueryModel *modelTypeTsh = new QSqlQueryModel();
            modelTypeTsh->setQuery(*query);
            ui->tshTypeCombo->show();
            ui->tshLabelType->show();
            ui->tshTypeCombo->setModel(modelTypeTsh);
        }
        else
            qDebug()<<"Failed to Open connection";
    }
    else
    {
        ui->tshTypeCombo->hide();
        ui->tshLabelType->hide();
    }
}
