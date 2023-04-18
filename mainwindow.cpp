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

//Equipment
setEquipmentInterface();
 Equipment_CRUD() ;


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
ui->tableViewEquip->verticalHeader()->hide() ;

QStringList items;
items << "E_ID" << "QUANTITY" << "STATUS";

// Add the list of items to the QComboBoxFilter
ui->comboBoxFilterEquip->addItems(items);
// Assuming you have a QComboBox instance called comboBox

ui->spinBoxQuantityEquip->setRange(-1000, 1000);


//qDebug() << ui->comboBoxFilterEquip->currentText();
FilterEquip = ui->comboBoxFilterEquip->currentText();

ui->tableViewEquip->setModel(Etmp.search3(SearchEquip,FilterEquip)) ;

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

    foreach (QPushButton *wBut, tabsButtonsFrame->findChildren<QPushButton *>(
                                    QString(), Qt::FindDirectChildrenOnly)) {
      wBut->setCheckable(true);
      buttonGroup->addButton(wBut);
    }




    // Check the first button

    tabsButtonsFrame
        ->findChild<QPushButton *>("HomeBtn", Qt::FindDirectChildrenOnly)
        ->setChecked(true);

    // Setup the  sub menu buttons group

      QFrame * moTabsButtonsFrame = ui->LeftMenuSubContainer->findChild<QFrame *> ("frame_3",Qt::FindDirectChildrenOnly) ;
      QStackedWidget *  mowstacked = ui->stackedWidget  ;
      QButtonGroup * moButtonGroup = new QButtonGroup(this) ;

      foreach (QPushButton *mowbut,
               moTabsButtonsFrame->findChildren<QPushButton *>(
                   QString(), Qt::FindDirectChildrenOnly)) {
        mowbut->setCheckable(true);
        moButtonGroup->addButton(mowbut);
      }
//      qDebug() << moButtonGroup->buttons();

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




}
void  MainWindow:: Equipment_CRUD()
{  // CREATE
    connect(ui->AddEquipBtn, &QPushButton::clicked, this, [this]() {
        Equipment  E=GetEquipmentFromForm();

        bool test= E.Create();
        if(test)
        {
            ui->tableViewEquip->setModel(Etmp.search3(SearchEquip,FilterEquip)) ;
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
    });

// Double click for Update
    connect(ui->tableViewEquip, &QTableView::doubleClicked, this, [this](const QModelIndex& index){
        QString id = ui->tableViewEquip->model()->data(index.sibling(index.row(), 0)).toString();
        QString name = ui->tableViewEquip->model()->data(index.sibling(index.row(), 1)).toString();
        int serial = ui->tableViewEquip->model()->data(index.sibling(index.row(), 2)).toInt();
        QString manu = ui->tableViewEquip->model()->data(index.sibling(index.row(), 3)).toString();
        QDate p = ui->tableViewEquip->model()->data(index.sibling(index.row(), 4)).toDate();
        QDate e = ui->tableViewEquip->model()->data(index.sibling(index.row(), 5)).toDate();
        QString s = ui->tableViewEquip->model()->data(index.sibling(index.row(), 6)).toString();
        QString i = ui->tableViewEquip->model()->data(index.sibling(index.row(), 7)).toString();
        int q = ui->tableViewEquip->model()->data(index.sibling(index.row(), 8)).toInt();

        ui->lineEditIdEquip->setText(id);
        ui->spinBoxQuantityEquip->setValue(q);
        ui->spinBoxSerialEquip->setValue(serial);
        ui->lineEditManufacEquip->setText(manu);
        ui->comboBoxNameEquip->setCurrentText(name);
        ui->comboBoxStatusEquip->setCurrentText(s);
        ui->dateEditpEquip->setDate(p);
        ui->dateEditpEquip->setDate(e);
        ui->plainTextEditInfoEquip->setPlainText(i);
    });


    //Delete Equipment
    connect(ui->DeleteEquipBtn, &QPushButton::clicked, [=]() {
        QModelIndex index = ui->tableViewEquip->currentIndex();

        // Retrieve the data for the first column of the selected row
        QVariant data = ui->tableViewEquip->model()->data(index.sibling(index.row(), 0));
        int id  = data.toInt() ;

        bool test = Etmp.Delete(id) ;
        if (test) {
            ui->tableViewEquip->setModel(Etmp.search3(SearchEquip,FilterEquip)) ;
            QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Delete done\n Click cancel to exist"), QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("Ok"), QObject::tr("Delete done\n Click cancel to exist"), QMessageBox::Cancel);
        }
    });

//UPDATE
    connect(ui->UpdateEquipBtn, &QPushButton::clicked, this, [this]() {

        Equipment  E=GetEquipmentFromForm();
        if (on_lineEditManufacEquip_editingFinished()) {
            bool test = E.Update();
            if (test) {
                ui->tableViewEquip->setModel(Etmp.search3(SearchEquip,FilterEquip)) ;
                QMessageBox::information(nullptr, QObject::tr("Ok"), QObject::tr("Update done\n Click cancel to exist"), QMessageBox::Cancel);
            } else {
                QMessageBox::information(nullptr, QObject::tr("not ok\n"), QObject::tr("update not done\n Click cancel to exist"), QMessageBox::Cancel);
            }
        } else {
            QMessageBox::information(nullptr, QObject::tr("CONTROL\n"), QObject::tr("do not enter special characters"), QMessageBox::Cancel);
        }
    });



}



 //Input Control of manufacturer
bool MainWindow::on_lineEditManufacEquip_editingFinished()
{     bool local_test_manufacturer= true ;
      QString manu = ui->lineEditManufacEquip->text() ;
      for(int i=0;i<manu.length();i++)
      {
  if(manu[i]=="$" || manu[i]=="&" || manu[i]=="*" || manu[i]==",") local_test_manufacturer=false  ;
      }
      if(local_test_manufacturer==false ){
          ui->lineEditManufacEquip->setStyleSheet("background-color: red;")  ;
      ui->lineEditManufacEquip->show() ;
      }
      else
      {
         ui->lineEditManufacEquip->setStyleSheet("background-color: white;")  ;
         ui->lineEditManufacEquip->show() ;

      }
return local_test_manufacturer ;
}
Equipment MainWindow:: GetEquipmentFromForm()
{
    int id = ui->lineEditIdEquip->text().toInt();
    QString name = ui->comboBoxNameEquip->currentText();
    QString status = ui->comboBoxStatusEquip->currentText();
    int qu = ui->spinBoxQuantityEquip->value();
    int serial = ui->spinBoxSerialEquip->value();
    QString manu = ui->lineEditManufacEquip->text();
    QString info = ui->plainTextEditInfoEquip->toPlainText();
    QString purchase = ui->dateEditpEquip->text();
    QString expire = ui->dateEditeEquip->text();
    Equipment E(id, name, serial, manu, purchase, expire, status, info, qu);

    return E ;
}

void MainWindow::on_comboBoxFilterEquip_activated(const QString &arg1)
{  FilterEquip=arg1;

//    ui->tableViewEquip->setModel(Etmp.read_sortby(arg1)) ;
    ui->tableViewEquip->setModel(Etmp.search3(SearchEquip,FilterEquip)) ;

}


void MainWindow::on_lineEditSearchEquip_textChanged(const QString &arg1)
{
    SearchEquip=arg1;

        ui->tableViewEquip->setModel(Etmp.search3(SearchEquip,FilterEquip)) ;

}
void MainWindow:: Ambulance_CRUD()
{




}
void MainWindow::setWindowAmbulance()
{





}
