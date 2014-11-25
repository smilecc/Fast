#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QCloseEvent>

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
private slots:
  void onSystemTrayIconClicked(QSystemTrayIcon::ActivationReason reason);
  void on_actionExit_triggered();

protected:
  void closeEvent(QCloseEvent *event);
private:
  QSystemTrayIcon *trayicon;
  QMenu *trayiconMenu;
};

#endif // MAINWINDOW_H
