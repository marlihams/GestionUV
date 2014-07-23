#include "AutoCompletionAlgo.h"
#include "ui_AutoCompletionAlgo.h"

AutoCompletionAlgo::AutoCompletionAlgo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutoCompletionAlgo)
{
    ui->setupUi(this);
}

AutoCompletionAlgo::~AutoCompletionAlgo()
{
    delete ui;
}
