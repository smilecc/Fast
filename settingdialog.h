#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QCloseEvent>
#include <QAbstractButton>
#include "addprodialog.h"
#include "ui_addprodialog.h"

namespace Ui {
class SettingDialog;
}

class SettingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingDialog(Ui::SettingDialog *fromMainUi,QWidget *parent = 0);
    ~SettingDialog();
    bool isExit;
    void initWnd();
    QSettings *proSettings;
    QSettings *proListSettings;
private:
    Ui::SettingDialog *ui;
    AddProDialog *m_pAddProDialog;
    Ui::AddProDialog aWnd;
protected:
  void closeEvent(QCloseEvent *event);
private slots:
  void on_cancleButton_clicked();
  void on_addProButton_clicked();
  void on_deleteProButton_2_clicked();
  void on_saveButton_clicked();
  void on_addPro_commitButton_clicked();
};

#endif // SETTINGDIALOG_H
