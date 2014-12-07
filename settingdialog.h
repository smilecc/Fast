#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QCloseEvent>
#include <QAbstractButton>

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();
    bool isExit;
private:
    Ui::SettingDialog *ui;
protected:
  void closeEvent(QCloseEvent *event);
private slots:
  void on_cancleButton_clicked();
  void on_addProButton_clicked();
  void on_deleteProButton_2_clicked();
};

#endif // SETTINGDIALOG_H
