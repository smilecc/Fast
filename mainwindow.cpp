#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "QDebug"
#include "FastBin.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    ishide(false),isExit(false)
{
    ui->setupUi(this);
    //初始化主界面

    //初始化设置类
    this->settings = new QSettings ("Config.ini", QSettings::IniFormat);

    //初始化设置界面
    this->m_pSettingWnd = new SettingDialog(this);
    sWnd.setupUi(m_pSettingWnd);
    sWnd.tableWidget->setColumnWidth(0,180);//设置列宽
    sWnd.tableWidget->setColumnWidth(1,400);
    sWnd.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置不能修改
    sWnd.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置整行选择
    sWnd.tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//设置只能单行选择
    sWnd.lnkSeachCheckBox->setChecked(settings->value("SeachFromLnk").value<bool>());
    sWnd.lnkPathEdit->setText(settings->value("LnkPath").value<QString>());
    QObject::connect(sWnd.cancleButton, SIGNAL(clicked()), m_pSettingWnd , SLOT(on_cancleButton_clicked()));
    QObject::connect(sWnd.saveButton, SIGNAL(clicked()), this , SLOT(on_saveButton_clicked()));
    QObject::connect(sWnd.addProButton, SIGNAL(clicked()), m_pSettingWnd , SLOT(on_addProButton_clicked()));
    QObject::connect(sWnd.deleteProButton_2, SIGNAL(clicked()), m_pSettingWnd , SLOT(on_deleteProButton_2_clicked()));


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
    trayicon->showMessage("Loading...", "Loading Program...", QSystemTrayIcon::Information, 2000);
    //为系统托盘绑定单击信号的槽 即图标激活时
    connect(trayicon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason)));

    m_fb.LoadPro(settings->value("LnkPath").value<QString>(),settings->value("SeachFromLnk").value<bool>()); //初始化载入 LoadProgram
    for(int i=0;i<this->m_fb.m_SoftInfo.size();i++){
        sWnd.tableWidget->setRowCount(sWnd.tableWidget->rowCount()+1);
        sWnd.tableWidget->setItem(i,0,new QTableWidgetItem(m_fb.m_SoftInfo[i].icon,m_fb.m_SoftInfo[i].name));
        sWnd.tableWidget->setItem(i,1,new QTableWidgetItem(m_fb.m_SoftInfo[i].path));

    }
    trayicon->showMessage("Loading...", "Loaded successfully", QSystemTrayIcon::Information, 2000);
    ui->lineEdit->installEventFilter(this); //绑定事件过滤器
}

MainWindow::~MainWindow()
{
    delete ui;
}

//事件过滤器
bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{

     if (watched==ui->lineEdit)         //判断控件 lineEdit
     {
            if (event->type() == QEvent::KeyPress){
                    QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
                        if (keyEvent->key() == Qt::Key_Down){ //响应↑事件
                            ui->ProList->setCurrentRow(ui->ProList->currentRow()+1);
                        }else if (keyEvent->key() == Qt::Key_Up){ //响应↑事件
                            ui->ProList->setCurrentRow(ui->ProList->currentRow()-1);
                        }
                    }

     }
 return QWidget::eventFilter(watched,event);     // 将事件交给上层对话框
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
        ui->lineEdit->setFocus();
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
      ui->lineEdit->setFocus();
      break;
  default:
      break;
  }
}
//用于响应程序被关闭的事件
void MainWindow::closeEvent(QCloseEvent *event)
{
  if(isExit) {
      this->m_pSettingWnd->isExit=true;
      this->m_pSettingWnd->close();
      return;
  }
  if(trayicon->isVisible())
  {
      this->ishide = true;
      hide();
      trayicon->showMessage("FastRun", "I'm HERE!", QSystemTrayIcon::Information, 2000);
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
    ui->lineEdit->setFocus();
}

//编辑框输入事件的响应
void MainWindow::on_lineEdit_cursorPositionChanged(int arg1, int arg2)
{
    ui->ProList->clear();
    m_proList.clear();
    qDebug()<<ui->lineEdit->text();
    m_proList = m_fb.findPro(ui->lineEdit->text());
    for(int i=0;i<m_proList.size();i++){
        ui->ProList->addItem(new QListWidgetItem(m_proList[i].icon,m_proList[i].name));
    }
    switch(m_proList.size()){
        case 0:
            this->setGeometry(this->geometry().x(),this->geometry().y(),400,60);
            ui->ProList->setGeometry(10,60,381,0);
            break;
        case 1:
            this->setGeometry(this->geometry().x(),this->geometry().y(),400,70+1*40);
            ui->ProList->setGeometry(10,60,381,40);
            break;
        case 2:
            this->setGeometry(this->geometry().x(),this->geometry().y(),400,70+2*40);
            ui->ProList->setGeometry(10,60,381,80);
            break;
        case 3:
            this->setGeometry(this->geometry().x(),this->geometry().y(),400,70+3*40);
            ui->ProList->setGeometry(10,60,381,120);
            break;
        default:
            this->setGeometry(this->geometry().x(),this->geometry().y(),400,70+4*40);
            ui->ProList->setGeometry(10,60,381,160);
    }
}
//响应enter事件
void MainWindow::on_lineEdit_returnPressed()
{
    qDebug()<<"press enter";
    if(this->m_proList.size() >= ui->ProList->currentRow()){
        if(this->m_fb.runPro(this->m_proList[ui->ProList->currentRow()].path)){
            this->ishide = true;
            hide();
        }
    }
}

void MainWindow::on_actionSettings_triggered()
{
    this->ishide = true;
    this->hide();
    this->m_pSettingWnd->show();
}

void MainWindow::on_saveButton_clicked()
{
    settings->setValue("SeachFromLnk",sWnd.lnkSeachCheckBox->isChecked());
    settings->setValue("LnkPath",sWnd.lnkPathEdit->text());
    this->m_pSettingWnd->hide();
    qDebug()<<"save";
}
