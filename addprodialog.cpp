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

void AddProDialog::clearEdit(){
    ui->proNameEdit->setText("");
    ui->proPathEdit->setText("");
}

void AddProDialog::on_cancleButton_clicked()
{
    this->hide();
}
