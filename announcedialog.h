#ifndef ANNOUNCEDIALOG_H
#define ANNOUNCEDIALOG_H

#include <QDialog>

namespace Ui {
class AnnounceDialog;
}

class AnnounceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AnnounceDialog(QWidget *parent = 0);
    ~AnnounceDialog();
    QString announceString;

public slots:
    void accept();

private:
    Ui::AnnounceDialog *ui;
};

#endif // ANNOUNCEDIALOG_H
