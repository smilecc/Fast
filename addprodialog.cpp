#include "addprodialog.h"
#include "ui_addprodialog.h"

AddProDialog::AddProDialog(Ui::AddProDialog *fromMainUi, QWidget *parent) :
    QDialog(parent),
    ui(fromMainUi)
{
    ui->setupUi(this);
}

AddProDialog::~AddProDialog()
{
    //delete ui;
}
