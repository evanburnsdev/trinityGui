#include "announcedialog.h"
#include "ui_announcedialog.h"


AnnounceDialog::AnnounceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AnnounceDialog)
{
    ui->setupUi(this);
}

AnnounceDialog::~AnnounceDialog()
{
    delete ui;
}


void AnnounceDialog::accept()
{
//    DataObject dataObject;
//    announceString = dataObject.announceString;
    if(ui->checkBox->isChecked())
    {
        announceString.append(".gmannounce ");
    } else {
        announceString.append(".announce ");
    }
    announceString.append(ui->lineEdit->text());
    announceString.append("\n");
    this->done(1);
}


