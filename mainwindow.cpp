#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGlobal>
#include <QDebug>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  //Setting Window Functionalities
setWindowInterface();
// Setting Equipment tab
setEquipmentInterface();


}

MainWindow::~MainWindow() { delete ui; }
void MainWindow::  setEquipmentInterface()
{
    ui->comboBoxStatusEquip->addItem("Expired")  ;
    ui->comboBoxStatusEquip->addItem("Valid") ;

    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/téléchargement.jpg"),"Oxygen Tank") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/when-was-the-defibrillator-invented.jpg"),"Defibrillator") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/téléchargement (1).jpg"),"Heart monitor") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/png-clipart-intravenous-therapy-infusion-set-dialysis-catheter-syringe-catheter-miscellaneous-blue-thumbnail.png")
                              ,"IV") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/spine board.jpg"),"Spine Board") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/neckcollar.jpg"),"Neck Collar") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/suction device.jpg"),"Suction device") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/stretcher-bed-ramp.jpg"),"Stretcher ramp") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/firstaid.png"),"First aid kit") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/blankets and pillows.jpeg"),"Blankets") ;
    ui->comboBoxNameEquip->addItem(QIcon(":/equipment/img/gloves.jpg"),"gloves and gowns") ;

}

void MainWindow :: setWindowInterface()
{
    setWindowFlag(Qt::FramelessWindowHint);
    ui->SizeGrip->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    ui->MenuBtn->setCheckable(true);
    ui->MenuBtn->setChecked(false);


    // Setup custom control buttons

    connect(ui->CloseBtn, &QPushButton::clicked, this, &QMainWindow::close);
    connect(ui->RestoreBtn, &QPushButton::clicked, this,
            [this]() { isMaximized() ? showNormal() : showMaximized(); });
    connect(ui->MinimizeBtn, &QPushButton::clicked, this,
            &QMainWindow::showMinimized);

    // Setup the button group

    QFrame *tabsButtonsFrame = ui->LeftMenuSubContainer->findChild<QFrame *>(
        "frame_2", Qt::FindDirectChildrenOnly);
    QStackedWidget *wStacked = ui->stackedWidget_3;
    QButtonGroup *buttonGroup = new QButtonGroup(this);

    {
      auto buttons = tabsButtonsFrame->findChildren<QPushButton *>(
          QString(), Qt::FindDirectChildrenOnly);
      for (QPushButton *wBut : qAsConst(buttons)) {
        wBut->setCheckable(true);
        buttonGroup->addButton(wBut);
      }
    }




    // Check the first button

    tabsButtonsFrame
        ->findChild<QPushButton *>("HomeBtn", Qt::FindDirectChildrenOnly)
        ->setChecked(true);

    // Setup the  sub menu buttons group

      QFrame * moTabsButtonsFrame = ui->LeftMenuSubContainer->findChild<QFrame *> ("frame_3",Qt::FindDirectChildrenOnly) ;
      QStackedWidget *  mowstacked = ui->stackedWidget  ;
      QButtonGroup * moButtonGroup = new QButtonGroup(this) ;
      {
          auto  mobuttons =  moTabsButtonsFrame->findChildren<QPushButton *> (
                      QString(),Qt::FindDirectChildrenOnly) ;

          for(QPushButton * mowbut: qAsConst(mobuttons))
          {
              mowbut->setCheckable(true) ;
              moButtonGroup->addButton(mowbut) ;
          }
      }
      qDebug() << moButtonGroup->buttons();

    // Connect button group to stacked widget

    connect(buttonGroup,
            qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked), wStacked,
            [=](QAbstractButton *clicked) {
              QString pageName = clicked->objectName().replace("Btn", "Page");
              QWidget *wPage = wStacked->findChild<QWidget *>(
                  pageName, Qt::FindDirectChildrenOnly);
              wStacked->setCurrentWidget(wPage);
            });

    //Connect 2nd button's group to another stacked widget

    connect(moButtonGroup,
            qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked), mowstacked,
            [=](QAbstractButton *clicked) {
              QString pageName = clicked->objectName().replace("Btn", "Page");
              QWidget *mowPage = mowstacked->findChild<QWidget *>(
                  pageName, Qt::FindDirectChildrenOnly);
              ui->CenterMenuContainer->show();
              mowstacked->setCurrentWidget(mowPage);
            });

    connect(ui->CloseMoBtn,&QPushButton::clicked ,ui->CenterMenuContainer,[this](){ ui->CenterMenuContainer->hide();}) ;


  connect(ui->CloseNotifBtn,&QPushButton::clicked,ui->PopupNotificationContainer,[this](){ ui->PopupNotificationContainer->hide();});


    connect(ui->MenuBtn, &QPushButton::clicked, ui->LeftMenuContainer,
            [this](bool checked) {
              // Create a property animation object
              QPropertyAnimation *animation =
                  new QPropertyAnimation(ui->LeftMenuContainer, "maximumWidth");

              const int endValue = checked ? 50 : 130;
              const int duration = 500;

              // Set the target value of the animation
              animation->setEndValue(endValue);

              // Set the duration of the animation in milliseconds
              animation->setDuration(duration);

              // Start the animation
              animation->start();
            });

    ui->tableView->setModel(Etmp.read()) ;

}

void MainWindow::on_AddEquipBtn_clicked()
{
    int id= ui->lineEditIdEquip->text().toInt() ;
        QString name = ui->comboBoxNameEquip->currentText() ;
        QString status = ui->comboBoxStatusEquip->currentText() ;
        int qu = ui->spinBoxQuantityEquip->value() ;
        int serial = ui->spinBoxSerialEquip->value() ;
        QString manu = ui->lineEditManufacEquip->text() ;
        QString  info = ui->plainTextEditInfoEquip->toPlainText()   ;
        QString  purchase = ui->dateEditpEquip->text() ;
        QString expire = ui->dateEditeEquip->text() ;
        Equipment  E(id,name,serial,manu,purchase,expire,status,info,qu);
        bool test= E.Create();
        if(test)
        {
            ui->tableView->setModel(Etmp.read()) ;
         QMessageBox ::information(nullptr,QObject::tr("Ok"),QObject::tr("Insert done\n Click cancel to exist"),QMessageBox::Cancel);
         ui->spinBoxSerialEquip->clear();
         ui->spinBoxQuantityEquip->clear() ;
         ui->lineEditManufacEquip->clear();
        ui->lineEditIdEquip->clear() ;
        ui->plainTextEditInfoEquip->clear() ;
        ui->dateEditpEquip->clear();
        ui->dateEditeEquip->clear() ;

        }
        else
        {
            QMessageBox ::critical(nullptr,QObject::tr("Not Ok"),QObject::tr("Insert Not done\n Click cancel to exist"),QMessageBox::Cancel);

        }


}
