#include "dataobject.h"
bool csvDone;
DataObject::DataObject(QObject *parent) :
    QObject(parent)
{
    csvDone = true;
    dataModel = new QStandardItemModel;
    needCSV = true;
    connect(dataModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(onDataModelDataEntered() ) );

}

void DataObject::onDataModelDataEntered()
{
    emit this->modelDataEntered(needCSV);
    needCSV = false;
}


void DataObject::neededCSV(const bool &chooserNeedCSV)
{
    csvDone = chooserNeedCSV;
}

void DataObject::onCsvRequestSent(const bool &csvRequest)
{
    if(csvDone == true)
    {
        QStringList rowData;
        QStringList columnData;
        QString fileName;
        QString data;
 //       fileName = QFileDialog::getOpenFileName(this, ("Open Table"), "~/", ("CSV_File(*.csv)"));
        QFile importedCSV("./table.csv");
        data.clear();
        columnData.clear();
        rowData.clear();
        if (importedCSV.open(QFile::ReadOnly))
        {
            data = importedCSV.readAll();
            rowData = data.split("\n");
            importedCSV.close();
        }
        qDebug() << "Step 1 Complete";
//        dataTableWidget = new QTableWidget;
        dataModel = new QStandardItemModel;
//        dataTableWidget->setRowCount(rowData.size());
        dataModel->setRowCount(rowData.size());
//        dataTableWidget->setColumnCount(145);
        dataModel->setColumnCount(145);
        for (int x = 0; x < rowData.count()-1; x++)
        {
            columnData = rowData.at(x).split(",");
            for (int y = 0; y < columnData.count(); y++)
            {
//                QTableWidgetItem *newTableItem = new QTableWidgetItem(columnData[y]);
                QStandardItem *newItem = new QStandardItem(columnData[y]);
//                dataTableWidget->setItem(x,y, newTableItem);
                dataModel->setItem(x,y, newItem);
            }

        }
        qDebug() << "widget loaded";
        qDebug() << dataModel->item(10000, 4)->text();
//        qDebug() << dataTableWidget->itemAt(0,5)->text().toAscii();
    }
    this->onCSVWasImported();

}
void DataObject::onCSVWasImported()
{
    emit this->loadedCSV(dataModel);
    qDebug() << "test";
}
