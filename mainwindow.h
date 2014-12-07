#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>
#include "FastBin.h"
#include "settingdialog.h"
#include "ui_settingdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isExit;
    QSettings *settings;
public slots:

    void activated();

private:
    Ui::MainWindow *ui;
    bool ishide;
    FastBin m_fb;
    std::vector<SoftInfo> m_proList;
    SettingDialog *m_pSettingWnd;
    Ui::SettingDialog sWnd;
private slots:
  void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
  void on_actionExit_triggered();

  void on_actionDisplay_triggered();

  void on_lineEdit_cursorPositionChanged(int arg1, int arg2);
  bool eventFilter(QObject *,QEvent *);
  void on_lineEdit_returnPressed();

  void on_actionSettings_triggered();
  void on_saveButton_clicked();
protected:
  void closeEvent(QCloseEvent *event);
private:
  QSystemTrayIcon *trayicon;
  QMenu *trayiconMenu;
};

#endif // MAINWINDOW_H
