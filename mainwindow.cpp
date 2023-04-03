#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGlobal>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowFlag(Qt::FramelessWindowHint);

  ui->SizeGrip->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

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

  // Connect button group to stacked widget

  connect(buttonGroup,
          qOverload<QAbstractButton *>(&QButtonGroup::buttonClicked), this,
          [=](QAbstractButton *clicked) {
            QString pageName = clicked->objectName().replace("Btn", "Page");
            QWidget *wPage = wStacked->findChild<QWidget *>(
                pageName, Qt::FindDirectChildrenOnly);
            wStacked->setCurrentWidget(wPage);
          });
}

MainWindow::~MainWindow() { delete ui; }
