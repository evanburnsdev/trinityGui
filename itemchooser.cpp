#include "itemchooser.h"
#include "ui_itemchooser.h"

QString raceFilter;
QString classFilter;
QString typeFilter;

ItemChooser::ItemChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemChooser)
{
    keyData = new QStringList;
    ui->setupUi(this);
    this->setupFilters();
 //   connect(ui->raceCombo, SIGNAL(activated(QString)), this, SLOT(setupFilters()));
}

ItemChooser::~ItemChooser()
{
    delete ui;
}

void ItemChooser::setupFilters()
{

    ui->raceCombo->addItem("");          //Column 14
    ui->raceCombo->addItem("Human");     //1
    ui->raceCombo->addItem("Orc");       //2
    ui->raceCombo->addItem("Dwarf");     //3
    ui->raceCombo->addItem("Night Elf"); //4
    ui->raceCombo->addItem("Undead");    //5
    ui->raceCombo->addItem("Tauren");    //6
    ui->raceCombo->addItem("Gnome");     //7
    ui->raceCombo->addItem("Troll");     //8
    ui->raceCombo->addItem("Blood Elf"); //10
    ui->raceCombo->addItem("Draenei");   //11

    ui->classCombo->addItem("");            //Column 2 or 13?
    ui->classCombo->addItem("Warrior");     //1
    ui->classCombo->addItem("Paladin");     //2
    ui->classCombo->addItem("Hunter");      //3
    ui->classCombo->addItem("Rogue");       //4
    ui->classCombo->addItem("Priest");      //5
    ui->classCombo->addItem("Deathknight"); //6
    ui->classCombo->addItem("Shaman");      //7
    ui->classCombo->addItem("Mage");        //8
    ui->classCombo->addItem("Warlock");     //9
    ui->classCombo->addItem("Druid");       //11

    /*  Column 12
     *  0= ammo
        1 = head
        2 = neck
        3 = shoulder
        4 = shirt
        5 = chest
        6 = belt
        7 = legs
        8 = feet
        9 = wrist
        10 = gloves
        11 = finger 1
        12 = finger 2
        13 = trinket 1
        14 = trinket 2
        15 = back
        16 = main hand
        17 = off hand
        18 = ranged
        19 = tabard
        20 = first bag (the rightmost one)
        21 = second bag
        22 = third bag
        23 = fourth bag (the leftmost one)
        */

    ui->typeCombo->addItem("");
    ui->typeCombo->addItem("Weapon");     //16, 17, 18
    ui->typeCombo->addItem("Armor");      //1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 19
    ui->typeCombo->addItem("Containers"); //20, 21, 22, 23

}

void ItemChooser::updateClickHandler()
{
    int raceInt = ui->raceCombo->currentIndex();
    raceFilter.setNum(raceInt);
    ui->tlabel->setText(raceFilter);
    bool match = false;
    for( int y=0; y< ui->tableWidget->rowCount()-1; y++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(y, 14);
        if( item->text().contains(raceFilter) )
        {
            match = true;
        } else if (raceFilter == "0")
        {
            match = true;
        } else if (raceFilter != "0" && item->text() == "-1")
        {
            match = false;
        } else
        {
            match = false;
        }
        ui->tableWidget->setRowHidden(y, !match);
    }
    int classInt = ui->classCombo->currentIndex();
    classFilter.setNum(classInt);

    for (int y=0; y< ui->tableWidget->rowCount()-1; y++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(y, 13);
        if (item->text().contains(classFilter) )
        {
            match = true;
        } else if (ui->tableWidget->isRowHidden(y) == true)
        {
            match = false;
        } else
        {
            match = false;
        }
        ui->tableWidget->setRowHidden(y, !match);
    }
}

void ItemChooser::importCSVFile()
{
    QStringList rowData;
    QStringList columnData;
    QString fileName;
    QString data;
    fileName = QFileDialog::getOpenFileName(this, ("Open Table"), "~/", ("CSV_File(*.csv)"));
    QFile importedCSV(fileName);
    data.clear();
    columnData.clear();
    rowData.clear();
    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        rowData = data.split("\n");
        importedCSV.close();
    }
    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setRowCount(rowData.size());
    ui->tableWidget->setColumnCount(139);
    for (int x = 0; x < rowData.size(); x++)
    {
        columnData = rowData.at(x).split(",");
        for (int y = 0; y < columnData.size(); y++)
        {
            QTableWidgetItem *newWidgetItem = new QTableWidgetItem(columnData[y]);
            ui->tableWidget->setItem(x,y, newWidgetItem);
        }
    }
    ui->tableWidget->resizeColumnsToContents();
}

void ItemChooser::importKey()
{
    QString fileName;
    QString data;
    fileName = QFileDialog::getOpenFileName(this, ("Open Key"), "~/", ("CSV_File(*.csv)"));
    QFile importedCSV(fileName);
    data.clear();
    if (importedCSV.open(QFile::ReadOnly))
    {
        data = importedCSV.readAll();
        importedCSV.close();
    }
    keyData->append(data.split(","));
    for (int x = 0; x < keyData->size(); x++)
    {
        QTableWidgetItem *newWidgetItem = new QTableWidgetItem(keyData->at(x));
        ui->tableWidget->setHorizontalHeaderItem(x, newWidgetItem);
 //       ui->tableWidget->setItem(0, x, newWidgetItem);
    }

}
