#include "settingdialog.h"
#include "ui_settingdialog.h"
#include "mainwindow.h"
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

}

SettingDialog::~SettingDialog()
{
    //delete ui;
}

//用于响应程序被关闭的事件
void SettingDialog::closeEvent(QCloseEvent *event)
{
  if(this->isExit) {
      qDebug()<<"program close";
      return;
  }
    qDebug()<<"setting wnd close";
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
    this->m_pAddProDialog->show();
}

void SettingDialog::on_deleteProButton_2_clicked()
{
    qDebug()<<"deleteProButton_2_clicked";
}

void SettingDialog::on_saveButton_clicked()
{
    this->proSettings->setValue("SeachFromLnk",ui->lnkSeachCheckBox->isChecked());
    this->proSettings->setValue("LnkPath",ui->lnkPathEdit->text());
    this->proSettings->setValue("Uninstall",ui->uninstallCheckBox->isChecked());
    this->hide();
    qDebug()<<"save";
}

