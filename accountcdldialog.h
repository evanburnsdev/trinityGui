#ifndef ACCOUNTCDLDIALOG_H
#define ACCOUNTCDLDIALOG_H

#include <QDialog>

namespace Ui {
class AccountCDLDialog;
}

class AccountCDLDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AccountCDLDialog(QWidget *parent = 0);
    ~AccountCDLDialog();
    QString accountString;

public slots:
    void createCheckStateHandler();
    void deleteCheckStateHandler();
    void passwordCheckStateHandler();
    void accept();
    
private:
    Ui::AccountCDLDialog *ui;
};

#endif // ACCOUNTCDLDIALOG_H
