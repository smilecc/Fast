#include "mainwindow.h"
#include <QApplication>
#include "MyGlobalShortCut/MyGlobalShortCut.h"
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    // 用法

    MyGlobalShortCut *shortcut = new MyGlobalShortCut("Alt+Space",&w);
    QObject::connect(shortcut,SIGNAL(activated()),&w,SLOT(activated()));



    /*
    QSystemTrayIcon systray;
    systray.setIcon(QIcon(":/ic/f.png"));
    systray.setVisible(true);*/

    return a.exec();
}
