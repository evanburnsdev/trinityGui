#include <QApplication>
#include "mainwindow.h"
#include "QStyleFactory"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(QStyleFactory::create( "cleanlooks"));

    MainWindow w;
    w.show();



    return a.exec();
}
