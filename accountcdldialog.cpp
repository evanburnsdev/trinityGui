#include "accountcdldialog.h"
#include "ui_accountcdldialog.h"

AccountCDLDialog::AccountCDLDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountCDLDialog)
{
    ui->setupUi(this);
    ui->passwordLine->setEchoMode(QLineEdit::Password);
    ui->passwordLine->setVisible(false);

}

AccountCDLDialog::~AccountCDLDialog()
{
    delete ui;
}

void AccountCDLDialog::createCheckStateHandler()
{
    if(ui->createCheck->isChecked()==true)
    {
        ui->passwordLine->setEnabled(true);
        ui->passwordLine->setVisible(true);
        ui->deleteCheck->setChecked(false);
        ui->deleteCheck->setEnabled(false);
        ui->passwordCheck->setChecked(false);
        ui->passwordCheck->setEnabled(false);
    } else
    {
        ui->passwordLine->setVisible(false);
        ui->deleteCheck->setEnabled(true);
        ui->passwordCheck->setEnabled(true);
    }
}

void AccountCDLDialog::deleteCheckStateHandler()
{
    if(ui->deleteCheck->isChecked()==true)
    {
        ui->createCheck->setChecked(false);
        ui->createCheck->setEnabled(false);
        ui->passwordCheck->setChecked(false);
        ui->passwordCheck->setEnabled(false);
    } else
    {
        ui->createCheck->setEnabled(true);
        ui->passwordCheck->setEnabled(true);
    }
}

void AccountCDLDialog::passwordCheckStateHandler()
{
    if(ui->passwordCheck->isChecked()==true)
    {
        ui->passwordLine->setEnabled(true);
        ui->passwordLine->setVisible(true);
        ui->createCheck->setChecked(false);
        ui->createCheck->setEnabled(false);
        ui->deleteCheck->setChecked(false);
        ui->deleteCheck->setEnabled(false);
    } else
    {
        ui->createCheck->setEnabled(true);
        ui->deleteCheck->setEnabled(true);
        ui->passwordLine->setEnabled(false);
        ui->passwordLine->setVisible(false);
    }
}


void AccountCDLDialog::accept()
{
    accountString.append("account ");
    if(ui->createCheck->isChecked()==true)
    {
        accountString.append("create ");
        accountString.append(ui->lineEdit->text());
        accountString.append(" ");
        accountString.append(ui->passwordLine->text());
    } else if(ui->deleteCheck->isChecked()==true) {
        accountString.append("delete ");
        accountString.append(ui->lineEdit->text());
    } else if(ui->passwordCheck->isChecked()==true)
    {
        accountString.append("set password ");
        accountString.append(ui->lineEdit->text());
        accountString.append(" ");
        accountString.append(ui->passwordLine->text());
        accountString.append(" ");
        accountString.append(ui->passwordLine->text());
        accountString.append(" ");
    } else {
        this->done(1);
    }
    accountString.append("\n");
    this->done(1);
}
