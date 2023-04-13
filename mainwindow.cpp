#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGlobal>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

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
        qDebug() << mobuttons ;

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
            qDebug() <<  pageName ;
            QWidget *mowPage = mowstacked->findChild<QWidget *>(
                pageName, Qt::FindDirectChildrenOnly);
            mowstacked->setCurrentWidget(mowPage);
          });





 /* connect(ui->SettingsBtn, &QPushButton::clicked, ui->CenterMenuContainer,
          [this]() { ui->CenterMenuContainer->show(); });

  connect(ui->InfoBtn, &QPushButton::clicked, ui->CenterMenuContainer,
          [this]() { ui->CenterMenuContainer->show(); });

  connect(ui->HelpBtn, &QPushButton::clicked, ui->CenterMenuContainer,
          [this]() { ui->CenterMenuContainer->show(); });*/

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

MainWindow::~MainWindow() { delete ui; }
