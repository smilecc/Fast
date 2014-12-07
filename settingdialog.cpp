#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <QDebug>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog),isExit(false)
{
    ui->setupUi(this);

}

SettingDialog::~SettingDialog()
{
    delete ui;
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

void SettingDialog::on_saveButton_clicked()
{
    qDebug()<<"save";
}



void SettingDialog::on_cancleButton_clicked()
{
    qDebug()<<"cancle";
}
