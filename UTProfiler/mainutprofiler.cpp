#include "mainutprofiler.h"
#include "ui_mainutprofiler.h"
#include "uvadddialog.h"
#include "dialogupdatedeleteuv.h"
#include "formationdialog.h"
#include "updatedeleteformation.h"
#include "uv_formationdialog.h"
#include"dossier.h"
#include <QTableWidget>
#include <QPushButton>
#include "ConsultDossier.h"
#include "AutoCompletionAlgo.h"
#include "UVsAsTableView.h"
#include "ViewFormationTable.h"
MainUTProfiler *MainUTProfiler::utProfiler=0;
MainUTProfiler::MainUTProfiler(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainUTProfiler)
{

    ui->setupUi(this);


}

MainUTProfiler::~MainUTProfiler()
{
    delete ui;
}



/*
This Slot Open the Window To Add a new UV
*/

void MainUTProfiler::on_addUV_clicked()
{
    UVAddDialog addUVD;
    addUVD.setModal(true);
    addUVD.exec();

}

void MainUTProfiler::on_updateDeleteUV_clicked()
{
    DialogUpdateDeleteUV updelUVD;
    updelUVD.setModal(true);
    updelUVD.exec();
}



void MainUTProfiler::on_addFormation_clicked()
{
    FormationDialog addFormation;
    addFormation.setModal(true);
    addFormation.exec();
}

void MainUTProfiler::on_updateVisFormation_clicked()
{
    UpdateDeleteFormation updateVis;
    updateVis.setModal(true);
    updateVis.exec();
}

void MainUTProfiler::on_addUVToFormation_clicked()
{
    UV_FormationDialog uvFormation;
    uvFormation.setModal(true);
    uvFormation.exec();
}





void MainUTProfiler::on_pushButton_7_clicked()
{

    Dossier dossierConstruction;
    dossierConstruction.setModal(true);

    dossierConstruction.exec();
}



void MainUTProfiler::on_consulterDossier_clicked()
{
    ConsultDossier  consDossier;
    consDossier.setModal(true);
    consDossier.exec();
}

void MainUTProfiler::on_simulateState_clicked()
{
    AutoCompletionAlgo  algoDialog;
    algoDialog.setModal(true);
    algoDialog.exec();
}

void MainUTProfiler::on_showUvsTable_clicked()
{
    UVsAsTableView tableUView;
    tableUView.setModal(true);
    tableUView.exec();
}

void MainUTProfiler::on_pushButton_clicked()
{
    ViewFormationTable formationView;
    formationView.setModal(true);
    formationView.exec();

}
