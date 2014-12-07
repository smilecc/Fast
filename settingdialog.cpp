#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "mainwindow.h"
#include <QMessageBox>
#include <QDebug>

SettingDialog::SettingDialog(Ui::SettingDialog *fromMainUi,QWidget *parent) :
    QDialog(parent),
    ui(fromMainUi),isExit(false)
{
    ui->setupUi(this);
    //初始化设置类
    this->proSettings = new QSettings ("Config.ini", QSettings::IniFormat);
    this->proListSettings = new QSettings ("ProListConfig.ini", QSettings::IniFormat);

    //初始化AddPro窗口
    this->m_pAddProDialog = new AddProDialog(&aWnd,this);
    QObject::connect(aWnd.commitButton,SIGNAL(clicked()),this,SLOT(on_addPro_commitButton_clicked()));

}

SettingDialog::~SettingDialog()
{
    //delete ui;
}
//初始化窗口中的项目
void SettingDialog::initWnd(){
    ui->lnkSeachCheckBox->setChecked(proSettings->value("SeachFromLnk").value<bool>());
    ui->lnkPathEdit->setText(proSettings->value("LnkPath").value<QString>());
    ui->uninstallCheckBox->setChecked(proSettings->value("Uninstall").value<bool>());
    int rowCount = this->proListSettings->value("Row").value<int>();
    for(int i=0;i<rowCount;i++){
        ui->proTableWidget->setRowCount(i+1);
        ui->proTableWidget->setItem(i,0,new QTableWidgetItem(this->proListSettings->value(QString(i)+"name").value<QString>()));
        ui->proTableWidget->setItem(i,1,new QTableWidgetItem(this->proListSettings->value(QString(i)+"path").value<QString>()));
    }
}


//用于响应程序被关闭的事件
void SettingDialog::closeEvent(QCloseEvent *event)
{
  if(this->isExit) {
      qDebug()<<"program close";
      return;
  }
    qDebug()<<"setting wnd close";
    this->initWnd();
    this->hide();
    event->ignore();

}



void SettingDialog::on_cancleButton_clicked()
{
    qDebug()<<"cancle";
    this->close();
}

void SettingDialog::on_addProButton_clicked()
{
    qDebug()<<"addProButton_clicked";
    this->m_pAddProDialog->clearEdit();
    this->m_pAddProDialog->show();
}

void SettingDialog::on_deleteProButton_2_clicked()
{
    qDebug()<<"deleteProButton_2_clicked";
    ui->proTableWidget->removeRow(ui->proTableWidget->currentRow());
}

void SettingDialog::on_saveButton_clicked()
{
    this->proSettings->setValue("SeachFromLnk",ui->lnkSeachCheckBox->isChecked());
    this->proSettings->setValue("LnkPath",ui->lnkPathEdit->text());
    this->proSettings->setValue("Uninstall",ui->uninstallCheckBox->isChecked());
    this->proListSettings->setValue("Row",ui->proTableWidget->rowCount());
    for(int i=0;i<ui->proTableWidget->rowCount();i++){
        this->proListSettings->setValue(QString(i)+"name",ui->proTableWidget->item(i,0)->text());
        this->proListSettings->setValue(QString(i)+"path",ui->proTableWidget->item(i,1)->text());
    }
    this->hide();
    qDebug()<<"save";
}

void SettingDialog::on_addPro_commitButton_clicked(){
    qDebug()<<"on_addPro_commitButton_clicked";
    if(aWnd.proPathEdit->text() == ""){
        QMessageBox::information(this, "ERROR", "The Program/File edit is empty!", QMessageBox::Ok);
        return;
    }
    m_pAddProDialog->hide();
    int tableRow = ui->proTableWidget->rowCount();
    ui->proTableWidget->setRowCount(tableRow+1);
    ui->proTableWidget->setItem(tableRow,0,new QTableWidgetItem(aWnd.proNameEdit->text()));
    ui->proTableWidget->setItem(tableRow,1,new QTableWidgetItem(aWnd.proPathEdit->text()));
}
