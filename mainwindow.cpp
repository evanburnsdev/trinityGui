#include "mainwindow.h"
#include "ui_mainwindow.h"

QStringList arguments;
QPalette authTextPalette;
QPalette worldTextPalette;
QObject *authParent;
QObject *worldParent;
QProcess *myAuthProcess = new QProcess(authParent);
QProcess *myWorldProcess = new QProcess(worldParent);
QTableWidget *itemTable;
QStringList *keyData;
QMenu *comeToMeSubMenu;
QMenu *addItemSubMenu;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    itemTable = new QTableWidget;
    keyData = new QStringList;

    //Setup Color Palettes
    authTextPalette = ui->AuthLabel->palette();
    worldTextPalette = ui->WorldLabel->palette();

    //Set Signal/Slots
    connect(myAuthProcess, SIGNAL(readyReadStandardError() ), this, SLOT(authReadyReadStandardError() ) );
    connect(myWorldProcess, SIGNAL(readyReadStandardError() ), this, SLOT(worldReadyReadStandardError() ) );
    connect(myWorldProcess, SIGNAL(readyRead() ), this, SLOT(worldTextSent()));
    connect(myAuthProcess, SIGNAL(started() ), this, SLOT(authProcessStarting()));
    connect(myAuthProcess, SIGNAL(finished(int) ), this, SLOT(authProcessStopping()));
    connect(myWorldProcess, SIGNAL(started() ), this, SLOT(worldProcessStarting()));
    connect(myWorldProcess, SIGNAL(finished(int) ), this, SLOT(worldProcessStopping()));




        /***********************************
         *The following will set up the menu
         **********************************/

        // File Menu
        QAction *fileMenu;
        fileMenu  = new QAction("&File", this);
        menuBar()->addAction(fileMenu);

        if(true){ //File Submenu

            QMenu *fileSubMenu = new QMenu();
            fileMenu->setMenu(fileSubMenu);

            if(true){
                //Select Item DB Action
                QAction *selectItem = new QAction("&Select Item List", this);
                fileSubMenu->addAction(selectItem);
                connect(selectItem, SIGNAL(triggered() ), this, SLOT(itemchooserwindow() ) );

                //Select Item Key
                QAction *selectKey = new QAction("Select Item Key", this);
                fileSubMenu->addAction(selectKey);
                connect(selectKey, SIGNAL(triggered() ), this, SLOT(keyChooserWindow() ) );

                //Exit Action
                QAction *exitAction = new QAction("&Exit", this);
                fileSubMenu->addAction(exitAction);
                connect(exitAction, SIGNAL(triggered() ), this, SLOT(exitClickHandler() ) );
            }
        }

        //Command Menu
        QAction *commandMenu;
        commandMenu = new QAction("&Commands", this);
        menuBar()->addAction(commandMenu);

        if(true){   //Command Submenu

            QMenu *commandSubMenu = new QMenu();
            commandMenu->setMenu(commandSubMenu);

            if(true){
                //account Menu
                QAction *accountMenu = new QAction(".&account", this);
                commandSubMenu->addAction(accountMenu);

                if(true)  //account Submenu
                {

                    QMenu *accountSubMenu = new QMenu();
                    accountMenu->setMenu(accountSubMenu);

                    if(true)
                    {
                        //create Action
                        QAction *accountCreate = new QAction("&create", this);
                        accountSubMenu->addAction(accountCreate);
                        connect(accountCreate, SIGNAL(triggered() ), this, SLOT(accountCDL() ) );

                        //delete Action
                        QAction *accountDelete = new QAction("&delete", this);
                        accountSubMenu->addAction(accountDelete);
                        connect(accountDelete, SIGNAL(triggered() ), this, SLOT(accountCDL() ) );

                        //online list Action
                        QAction *onlineList = new QAction("&Online List", this);
                        accountSubMenu->addAction(onlineList);
                        connect(onlineList, SIGNAL(triggered() ), this, SLOT(accountList() ) );

                        //set Menu
                        QAction *setMenu = new QAction("&set", this);
                        accountSubMenu->addAction(setMenu);

                        if(true)
                        {
                            //set Submenu
                            QMenu *setSubMenu = new QMenu();
                            setMenu->setMenu(setSubMenu);

                            if(true)
                            {
                                //addon
                                QAction *addon = new QAction("&addon", this);
                                setSubMenu->addAction(addon);
                                connect(addon, SIGNAL(triggered() ), this, SLOT(accountCDL() ) );

                                //gmlevel
                                QAction *gmLevel = new QAction("&gmlevel", this);
                                setSubMenu->addAction(gmLevel);
                                connect(gmLevel, SIGNAL(triggered() ), this, SLOT(accountCDL() ) );

                                //password
                                QAction *password = new QAction("password", this);
                                setSubMenu->addAction(password);
                                connect(password, SIGNAL(triggered() ), this, SLOT(accountCDL() ) );
                            }
                        }
                    }
                }

                //add Item
                QAction *addItemAction = new QAction(".a&dditem", this);
                commandSubMenu->addAction(addItemAction);
                connect(addItemAction, SIGNAL(triggered() ), this, SLOT(keyChooserWindow() ) );

                //additem Submenu
                //addItemSubMenu = new QMenu();
                //addItemAction->setMenu(addItemSubMenu);

                //announce Action
                QAction *announceAction = new QAction(".a&nnounce", this);
                commandSubMenu->addAction(announceAction);
                connect(announceAction, SIGNAL(triggered() ), this, SLOT(announceClickHandler() ) );

                //ban Menu
                QAction *banMenu = new QAction(".&ban", this);
                commandSubMenu->addAction(banMenu);

                if(true)   //ban Submenu
                {

                    QMenu *banSubMenu = new QMenu();
                    banMenu->setMenu(banSubMenu);

                    if(true)
                    {
                        //account Action
                        QAction *accountAction = new QAction("&account", this);
                        banSubMenu->addAction(accountAction);

                        //character Action
                        QAction *characterAction = new QAction("&character", this);
                        banSubMenu->addAction(characterAction);

                        //ip Action
                        QAction *ipAction = new QAction("&ip", this);
                        banSubMenu->addAction(ipAction);
                    }
                }

                //baninfo Menu
                QAction *banInfoMenu = new QAction(".&baninfo", this);
                commandSubMenu->addAction(banInfoMenu);

                if(true) //baninfo Submenu
                {

                    QMenu *banInfoSubMenu = new QMenu();
                    banInfoMenu->setMenu(banInfoSubMenu);

                    if(true)
                    {
                        //account Action
                        QAction *accountAction = new QAction("&account", this);
                        banInfoSubMenu->addAction(accountAction);

                        //character Action
                        QAction *characterAction = new QAction("&character", this);
                        banInfoSubMenu->addAction(characterAction);

                        //ip Action
                        QAction *ipAction = new QAction("&ip", this);
                        banInfoSubMenu->addAction(ipAction);
                    }
                }

                //banlist Menu
                QAction *banListMenu = new QAction(".&banlist", this);
                commandSubMenu->addAction(banListMenu);

                if(true)  //banlist Submenu
                {

                    QMenu *banListSubMenu = new QMenu();
                    banListMenu->setMenu(banListSubMenu);

                    if(true)
                    {
                        //account Action
                        QAction *accountAction = new QAction("&account", this);
                        banListSubMenu->addAction(accountAction);

                        //character Action
                        QAction *characterAction = new QAction("&character", this);
                        banListSubMenu->addAction(characterAction);

                        //ip Action
                        QAction *ipAction = new QAction("&ip", this);
                        banListSubMenu->addAction(ipAction);
                    }
                }

                //character Menu
                QAction *characterMenu = new QAction(".&character", this);
                commandSubMenu->addAction(characterMenu);

                if(true) //character Submenu
                {

                    QMenu *characterSubMenu = new QMenu();
                    characterMenu->setMenu(characterSubMenu);

                    if(true)
                    {
                        //customize Action
                        QAction *customizeAction = new QAction("&customize", this);
                        characterSubMenu->addAction(customizeAction);

                        //change faction Action
                        QAction *changeFactionAction = new QAction("c&hangefaction", this);
                        characterSubMenu->addAction(changeFactionAction);

                        //change race Action
                        QAction *changeRaceAction = new QAction("ch&angerace", this);
                        characterSubMenu->addAction(changeRaceAction);

                        //deleted Action
                        QAction *deletedAction = new QAction("&deleted", this);
                        characterSubMenu->addAction(deletedAction);

                        //erase Action
                        QAction *eraseAction = new QAction("&erase", this);
                        characterSubMenu->addAction(eraseAction);

                        //level Action
                        QAction *levelAction = new QAction("&level", this);
                        characterSubMenu->addAction(levelAction);

                        //rename Action
                        QAction *renameAction = new QAction("&rename", this);
                        characterSubMenu->addAction(renameAction);

                        //reputation Action
                        QAction *reputationAction = new QAction("re&putation", this);
                        characterSubMenu->addAction(reputationAction);

                        //titles Action
                        QAction *titlesAction = new QAction("&titles", this);
                        characterSubMenu->addAction(titlesAction);
                    }
                }

                //combatstop Action
                QAction *combatStopAction = new QAction(".c&ombatstop", this);
                commandSubMenu->addAction(combatStopAction);

                //cometome Action
                QAction *comeToMeAction = new QAction(".cometome", this);
                commandSubMenu->addAction(comeToMeAction);

                //cometome Submenu
                comeToMeSubMenu = new QMenu();
                comeToMeAction->setMenu(comeToMeSubMenu);

                //commands Action
                QAction *commandsAction = new QAction(".&commands", this);
                commandSubMenu->addAction(commandsAction);
                connect(commandsAction, SIGNAL(triggered() ), this, SLOT(commandsClickHandler() ) );

                //event Menu
                QAction *eventMenu = new QAction(".&event", this);
                commandSubMenu->addAction(eventMenu);

                if(true)  //event Submenu
                {

                    QMenu *eventSubMenu = new QMenu();
                    eventMenu->setMenu(eventSubMenu);

                    if(true)
                    {
                        //activelist Action
                        QAction *activeListAction = new QAction("&activelist", this);
                        eventSubMenu->addAction(activeListAction);

                        //start Action
                        QAction *startAction = new QAction("&start", this);
                        eventSubMenu->addAction(startAction);

                        //ip Action
                        QAction *stopAction = new QAction("s&top", this);
                        eventSubMenu->addAction(stopAction);
                    }
                }

                //gm Menu
                QAction *gmMenu = new QAction(".&gm", this);
                commandSubMenu->addAction(gmMenu);

                if(true){ //gm Submenu

                    QMenu *gmSubMenu = new QMenu();
                    gmMenu->setMenu(gmSubMenu);

                    if(true){ //list Action

                        QAction *gmList = new QAction("&list", this);
                        gmSubMenu->addAction(gmList);
                        connect(gmList, SIGNAL(triggered() ), this, SLOT(gmListClickHandler() ) );
                    }
                }
            }
        }
}

MainWindow::~MainWindow()
{
    myAuthProcess->terminate();
    myWorldProcess->terminate();
    delete ui;
}

//Set Colors for Starting and Stopping:
void MainWindow::authProcessStarting()
{
    authTextPalette.setColor(ui->AuthLabel->foregroundRole(), Qt::green);
    ui->AuthLabel->setPalette(authTextPalette);
}

void MainWindow::authProcessStopping()
{
    authTextPalette.setColor(ui->AuthLabel->foregroundRole(), Qt::red);
    ui->AuthLabel->setPalette(authTextPalette);
}

void MainWindow::worldProcessStarting()
{
    worldTextPalette.setColor(ui->WorldLabel->foregroundRole(), Qt::green);
    ui->WorldLabel->setPalette(worldTextPalette);
}

void MainWindow::worldProcessStopping()
{
    worldTextPalette.setColor(ui->WorldLabel->foregroundRole(), Qt::red);
    ui->WorldLabel->setPalette(worldTextPalette);
}

//Set Read for Text Boxes
void MainWindow::authReadyReadStandardError()
{
    ui->authServerText->append(myAuthProcess->readAllStandardError());
}

void MainWindow::worldReadyReadStandardError()
{
    ui->worldServerText->append(myWorldProcess->readAllStandardError());
}

//Update World Text Box and Clear World Input
void MainWindow::worldTextSent()
{
    ui->worldServerText->append(myWorldProcess->readAll());
    ui->worldSendText->clear();
}




/**********************************************************************************************************************************
 *Buttons and Inputs:
 *********************************************************************************************************************************/


/*********************************************************************************
 *Menu Setup
 ********************************************************************************/

void MainWindow::exitClickHandler()
{
    myWorldProcess->terminate();
    myAuthProcess->terminate();
    this->close();
}

void MainWindow::accountCDL()
{
    AccountCDLDialog dialog(this);
    dialog.exec();
    QString string = dialog.accountString;
    myWorldProcess->write(string.toAscii());
}

void MainWindow::itemchooserwindow()
{
}

void MainWindow::keyChooserWindow()
{
    ItemChooser chooser(this);
    chooser.importCSVFile();
    chooser.importKey();
    chooser.exec();
//    itemTable = chooser.itemTable;
 //   keyData = chooser.keyData;

 /*   for (int i=0; i< keyData->size(); i++)
    {
        QAction *action = new QAction(keyData->at(i), this);
        addItemSubMenu->addAction(action);
        addItemSubMenu->setStyleSheet("* { menu-scrollable: 1 }");
        QMenu *subMenu = new QMenu;
        action->setMenu(subMenu);
        subMenu->setStyleSheet("* { menu-scrollable: 1 }");

        if(true)
        {
            for (int a=0; a< itemTable->rowCount()-1 ; a++)
            {
                QTableWidgetItem *newItem = itemTable->item(a,i);
                QAction *ab = new QAction(this);
                ab->setText(newItem->text());
                subMenu->addAction(ab);
            }
        }

    }*/
}

void MainWindow::accountList()
{
    myWorldProcess->write("account onlinelist\n");
}

void MainWindow::announceClickHandler()
{
    AnnounceDialog dialog(this);
    dialog.exec();
    QString string = dialog.announceString;
    myWorldProcess->write(string.toAscii());
}

void MainWindow::commandsClickHandler()
{
    myWorldProcess->write(".commands\n");
}

void MainWindow::gmListClickHandler()
{
    myWorldProcess->write(".gm list\n");
}




/*********************************************************************************
 *Regular Buttons
 ********************************************************************************/
void MainWindow::authStartButtonClickHandler()
{
    myAuthProcess->start("./authserver");
}

void MainWindow::worldStartButtonClickHandler()
{
    myWorldProcess->start("./worldserver");
}

void MainWindow::authStopButtonClickHandler()
{
    myAuthProcess->terminate();
}

void MainWindow::worldStopButtonClickHandler()
{
    myWorldProcess->terminate();
}

void MainWindow::worldSendButtonClickHandler()
{
    QString worldString = ui->worldSendText->text();
    worldString.append("\n");
    myWorldProcess->write(worldString.toAscii());
}

