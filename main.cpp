#include <QApplication>
#include "mainwindow.h"
#include "QStyleFactory"
#include "dataobject.h"
#include "itemchooser.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setStyle(QStyleFactory::create( "cleanlooks"));

    MainWindow w;
    w.show();
    DataObject d;
    ItemChooser i;
    //i.importCSVFile();
    //i.importKey();

    QObject::connect(&d, SIGNAL(modelDataEntered(const bool&)),
                     &i, SLOT(onDataModelDataEntered(const bool&)));
    QObject::connect(&w, SIGNAL(csvRequestSent(const bool&)),
                     &d, SLOT(onCsvRequestSent(const bool&)));
    QObject::connect(&d, SIGNAL(loadedCSV(QStandardItemModel*&)),
                      &i, SLOT(loadedCSV(QStandardItemModel*&)));
    QObject::connect(&i, SIGNAL(neededCSV(const bool &)),
                     &d, SLOT(neededCSV(const bool &)));

    return a.exec();
}
