#ifndef ITEMCHOOSER_H
#define ITEMCHOOSER_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QTableWidget>
#include <QVector>
#include <QAction>
#include <QMenu>

namespace Ui {
class ItemChooser;
}

class ItemChooser : public QDialog
{
    Q_OBJECT
    
public:
    explicit ItemChooser(QWidget *parent = 0);
    ~ItemChooser();
    QStringList *keyData;

    
public slots:
void importCSVFile();
void importKey();
void setupFilters();
void updateClickHandler();

private slots:


private:
    Ui::ItemChooser *ui;
};

#endif // ITEMCHOOSER_H
