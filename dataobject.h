#ifndef DATAOBJECT_H
#define DATAOBJECT_H

#include <QObject>
#include <QStandardItemModel>
#include <QDebug>
#include <QTableWidget>
#include <QFile>

class DataObject : public QObject
{
    Q_OBJECT
public:
    explicit DataObject(QObject *parent = 0);
    QStandardItemModel *dataModel;
    QTableWidget *dataTableWidget;

public slots:
    void onCsvRequestSent(const bool &csvRequest);
    void neededCSV(const bool &chooserNeedCSV);

private slots:
    void onDataModelDataEntered();
    void onCSVWasImported();

signals:
    void modelDataEntered(const bool &dataModelUpdated);
    void loadedCSV(QStandardItemModel* &newDataModel);

private:
    bool needCSV;


    
};

#endif // DATAOBJECT_H
