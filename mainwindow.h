#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QProcess>
#include <QApplication>
#include <QVBoxLayout>
#include <QProcessEnvironment>
#include <QDialog>
#include <QMenuBar>
#include "announcedialog.h"

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
    void exitClickHandler();
    void gmListClickHandler();
    void commandsClickHandler();
    void announceClickHandler();


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
};

#endif // MAINWINDOW_H
