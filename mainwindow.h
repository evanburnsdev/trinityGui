#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QProcess>
#include <QApplication>
#include <QVBoxLayout>
#include <QProcessEnvironment>
#include <QDialog>
#include <QMenuBar>
#include <QDebug>
#include "announcedialog.h"
#include "accountcdldialog.h"
//#include "itemchooser.h"
//#include "dataobject.h"

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
    void accountCDL();
    void itemchooserwindow();

    void accountList();
    void announceClickHandler();
    void commandsClickHandler();
    void exitClickHandler();
    void gmListClickHandler();

    void authProcessStarting();
    void authProcessStopping();
    void worldProcessStarting();
    void worldProcessStopping();
    void authReadyReadStandardError();
    void worldReadyReadStandardError();
    void worldTextSent();

    void authStartButtonClickHandler();
    void authStopButtonClickHandler();
    void worldStartButtonClickHandler();
    void worldStopButtonClickHandler();
    void worldSendButtonClickHandler();

private:
    Ui::MainWindow *ui;

private slots:
    void keyChooserWindow();

signals:
    void csvRequestSent(const bool &csvRequest);
};

#endif // MAINWINDOW_H
