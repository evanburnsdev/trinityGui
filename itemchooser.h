#ifndef ITEMCHOOSER_H
#define ITEMCHOOSER_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QTableWidget>
#include <QTableView>
#include <QAction>
#include <QMenu>
#include <QStandardItemModel>

namespace Ui {
class ItemChooser;
}

class ItemChooser : public QDialog
{
    Q_OBJECT
    
public:
    explicit ItemChooser(QWidget *parent = 0);
    ~ItemChooser();

    
public slots:
    void onDataModelDataEntered(const bool &dataModelUpdated);
    void loadedCSV(QStandardItemModel* &newDataModel);
    void setupFilters();
    void updateClickHandler();
    void importKey();

private slots:

signals:
    void neededCSV(const bool &chooserNeedCSV);


private:
    Ui::ItemChooser *ui;
    QStandardItemModel *model;
    QStringList *keyData;
    bool cNeedCSV;
};

#endif // ITEMCHOOSER_H
