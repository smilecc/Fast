#ifndef ADDPRODIALOG_H
#define ADDPRODIALOG_H

#include <QDialog>

namespace Ui {
class AddProDialog;
}

class AddProDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddProDialog(Ui::AddProDialog *fromMainUi, QWidget *parent = 0);
    ~AddProDialog();
    void clearEdit();
private slots:
    void on_cancleButton_clicked();

private:
    Ui::AddProDialog *ui;
};

#endif // ADDPRODIALOG_H
