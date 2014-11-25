#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ishide(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::activated()
{
    //通过热键控制窗口的显示与隐藏
    if(!ishide){
        this->hide();
        ishide = true;
    }else{
        this->show();
        ishide = false;
    }
}
