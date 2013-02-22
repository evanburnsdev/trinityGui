#include "itemchooser.h"
#include "ui_itemchooser.h"

QString raceFilter;
QString classFilter;
QString typeFilter;
bool modelUpdated;

ItemChooser::ItemChooser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ItemChooser)
{
    keyData = new QStringList;
    ui->setupUi(this);
    cNeedCSV = true;
    this->setupFilters();
    modelUpdated = false;
}

ItemChooser::~ItemChooser()
{
    delete ui;
}

void ItemChooser::onDataModelDataEntered(const bool &dataModelUpdated)
{
    modelUpdated = dataModelUpdated;
}

void ItemChooser::loadedCSV(QStandardItemModel* &newDataModel)
{
    model = newDataModel;

    this->importKey();

    cNeedCSV = false;
    emit this->neededCSV(cNeedCSV);
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

    QSortFilterProxyModel *raceModel = new QSortFilterProxyModel(this);
    raceModel->setSourceModel(model);
    int raceInt = ui->raceCombo->currentIndex();
    raceFilter.setNum(raceInt);
    raceModel->setFilterKeyColumn(14);
    if(raceInt != 0)
    {
        raceModel->setFilterFixedString(raceFilter);
    }
    else
    {
        raceModel->setFilterFixedString("");
    }
    QSortFilterProxyModel *classModel = new QSortFilterProxyModel;
    classModel->setSourceModel(raceModel);
    int classInt = ui->classCombo->currentIndex();
    classFilter.setNum(classInt);
    classModel->setFilterKeyColumn(13);
    if(classInt != 0)
    {
        classModel->setFilterFixedString(classFilter);
    } else
    {
        classModel->setFilterFixedString("");
    }
    ui->tlabel->setText(raceFilter);

    QSortFilterProxyModel *itemIdModel = new QSortFilterProxyModel;
    itemIdModel->setSourceModel(classModel);
    itemIdModel->setFilterKeyColumn(0);
    itemIdModel->setFilterFixedString(ui->itemIdText->text());



    ui->tableView->setModel(itemIdModel);
}


void ItemChooser::importKey()
{
    if(cNeedCSV)
    {
        QString data;
        QString fileName;
//        fileName = QFileDialog::getOpenFileName(this, ("Open Key"), "~/", ("CSV_File(*.csv)"));
        QFile importedCSV("./key.csv");
        data.clear();
        if (importedCSV.open(QFile::ReadOnly))
        {
            data = importedCSV.readAll();
            importedCSV.close();
        }
        keyData->append(data.split(","));
        for (int x = 0; x < keyData->size(); x++)
        {
            QStandardItem *newItem = new QStandardItem(keyData->at(x));
            model->setHorizontalHeaderItem(x, newItem);
        }
        ui->tableView->verticalHeader()->setVisible(false);
        ui->tableView->setModel(model);
        qDebug() << "Step 2 Complete";
        qDebug() << "Step 3 Complete";
        qDebug() << model->item(0, 4)->text();

        QString widthData;
        QString widthFileName;
//        widthFileName = QFileDialog::getOpenFileName(this, ("Open ColumnWidth"), "~/", ("CSV_File(*.csv)"));
        QFile importedWidthCSV("./columnsize.csv");
        widthData.clear();
        if (importedWidthCSV.open(QFile::ReadOnly))
        {
            widthData = importedWidthCSV.readAll();
            importedWidthCSV.close();
        }
        QStringList widthDataList = widthData.split("\n");
        for (int i = 0; i < widthDataList.size(); i++)
        {
            ui->tableView->setColumnWidth(i, widthDataList.at(i).toInt());
        }
    } else
    {

    }
    this->show();

}

void ItemChooser::tableViewGetCoorid()
{
    QModelIndexList selectedIndex = ui->tableView->selectionModel()->selectedIndexes();
    int selectedRowInt = selectedIndex.at(0).row();
    int selectedColInt = selectedIndex.at(0).column();
    QString selectedRowString = QString::number(selectedRowInt);
    QString selectedColString = QString::number(selectedColInt);
    ui->tlabel->setText(selectedRowString);
    ui->yLabel->setText(selectedColString);
    ui->nameLabel->setText(ui->tableView->model()->data(ui->tableView->model()->index(selectedRowInt, 4)).toString());
    ui->qualityLabel->setText(ui->tableView->model()->data(ui->tableView->model()->index(selectedRowInt, 6)).toString()+" Quality");
    ui->itemLevelLabel->setText(ui->tableView->model()->data(ui->tableView->model()->index(selectedRowInt, 15)).toString()+" Item Level");
    ui->armorLabel->setText(ui->tableView->model()->data(ui->tableView->model()->index(selectedRowInt, 56)).toString()+" Armor");
    ui->blockLabel->setText(ui->tableView->model()->data(ui->tableView->model()->index(selectedRowInt, 112)).toString()+" Block");
    ui->materialLabel->setText(ui->tableView->model()->data(ui->tableView->model()->index(selectedRowInt, 108)).toString()+" Material");
    ui->bindingsLabel->setText(ui->tableView->model()->data(ui->tableView->model()->index(selectedRowInt, 101)).toString()+" Bindings");
    /*
     *Bonding 101???
     *-1 Binds when picked up
     * 0 No binding?
     * 1 Binds to Battle.net account
     * 2 Binds when equiped
     *
     *
     *Material 7 = Cloth
     *          8 = Leather
     *          5 = Mail
     *
     *
     *Agility = 3
    Strength = 4
    Intellect = 5
    Spirit = 6
    Stamina = 7
    Defense Rating = 12
    Dodge Rating = 13
    Parry Rating = 14
    Block Rating = 15
    Melee Hit = 16
    Ranged Hit = 17
    Spell Hit = 18
    Melee Crit = 19
    Ranged Crit = 20
    Spell Crit = 21
    Melee Haste = 28
    Ranged Haste = 29
    Spell Haste = 30
    General Hit = 31
    General Crit = 32
    Resilience = 35
    General Haste = 36
    Expertise = 37
*/

}

void ItemChooser::accept()
{

    QModelIndexList selectedRow = ui->tableView->selectionModel()->selectedIndexes();
    int selectedInt = selectedRow.at(0).row();
    QString selectedRowString = ui->tableView->model()->data(ui->tableView->model()->index(selectedInt, 0)).toString();
    QString additem = ".additem";
 //   QString selectedRowString = ui->tableView->selectionModel();
    additem.append(" ");
    additem.append(selectedRowString);
    qDebug() << additem;
}
