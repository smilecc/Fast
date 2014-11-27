#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDebug"
#include "FastBin.h"
#include "FastBin.cpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ishide(false),isExit(false)
{
    ui->setupUi(this);
    trayicon = new QSystemTrayIcon(this);
    //创建QIcon对象，参数是图标资源，值为项目的资源文件中图标的地址
    QIcon icon(":/ic/f.png");
    trayiconMenu = new QMenu(this);

    //为托盘菜单添加菜单项
    trayiconMenu->addAction(ui->actionDisplay);
    trayiconMenu->addAction(ui->actionSettings);
    //分隔符
    trayiconMenu->addSeparator();
    trayiconMenu->addAction(ui->actionExit);

    //将创建的QIcon对象作为系统托盘图标
    trayicon->setIcon(icon);
    //显示托盘图标
    trayicon->show();
    //设置系统托盘提示
    trayicon->setToolTip("Fast");
    //将创建菜单作为系统托盘菜单
    trayicon->setContextMenu(trayiconMenu);
    //在系统托盘显示气泡消息提示
    trayicon->showMessage("Look here!!!", "I'm here!Fast does not shut!", QSystemTrayIcon::Information, 5000);
    //为系统托盘绑定单击信号的槽 即图标激活时
    connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));

    m_fb.LoadPro();


}

MainWindow::~MainWindow()
{
    delete ui;
}
//响应热键事件
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
//用于响应托盘图标被双击的事件
void MainWindow::onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason)
{
  switch(reason)
  {
  //单击
  case QSystemTrayIcon::Trigger:
  //双击
  case QSystemTrayIcon::DoubleClick:
      //恢复窗口显示
      this->setWindowState(Qt::WindowActive);
      this->ishide = false;
      this->show();
      break;
  default:
      break;
  }
}
//用于响应程序被关闭的事件
void MainWindow::closeEvent(QCloseEvent *event)
{
  if(isExit) return;
  if(trayicon->isVisible())
  {
      this->ishide = true;
      hide();
      event->ignore();
  }
}
//用于响应菜单栏中的退出按钮
void MainWindow::on_actionExit_triggered()
{
    isExit = true;
    this->close();
}
//用于响应菜单栏中的显示按钮
void MainWindow::on_actionDisplay_triggered()
{
    this->ishide = false;
    this->show();
}

//编辑框输入事件的响应
void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    FastBin FB;
    ui->ProList->clear();
    ui->ProList->addItem(new QListWidgetItem(FB.topy(ui->lineEdit->text())));
}
