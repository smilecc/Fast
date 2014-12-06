#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include "FastBin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

    void activated();

private:
    Ui::MainWindow *ui;
    bool ishide;
    bool isExit;
    FastBin m_fb;
    std::vector<SoftInfo> m_proList;
private slots:
  void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
  void on_actionExit_triggered();

  void on_actionDisplay_triggered();

  void on_lineEdit_cursorPositionChanged(int arg1, int arg2);
  bool eventFilter(QObject *,QEvent *);
  void on_lineEdit_returnPressed();

protected:
  void closeEvent(QCloseEvent *event);
private:
  QSystemTrayIcon *trayicon;
  QMenu *trayiconMenu;
};

#endif // MAINWINDOW_H
