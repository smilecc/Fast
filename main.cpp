#include "mainwindow.h"
#include <QApplication>
#include "MyGlobalShortCut/MyGlobalShortCut.h"
#include <QSystemTrayIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowFlags(Qt::WindowStaysOnTopHint);
    w.show();

    w.setGeometry(w.geometry().x(),w.geometry().y(),400,60);

    // 绑定快捷键
    MyGlobalShortCut *shortcut = new MyGlobalShortCut("Alt+Space",&w);
    QObject::connect(shortcut,SIGNAL(activated()),&w,SLOT(activated()));


    return a.exec();
}
