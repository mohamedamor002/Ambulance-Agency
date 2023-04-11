#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setWindowFlag(Qt::FramelessWindowHint);

  ui->SizeGrip->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

  // Setup custom control buttons

  connect(ui->CloseBtn, &QPushButton::clicked, this, &QPushButton::close);
  connect(ui->RestoreBtn, &QPushButton::clicked, this,
          [this]() { isMaximized() ? showNormal() : showMaximized(); });
  connect(ui->MinimizeBtn, &QPushButton::clicked, this,
          [this]() { setWindowState(Qt::WindowState::WindowMinimized); });

  // Setup the button group

  QFrame *tabsButtonsFrame = ui->LeftMenuSubContainer->findChild<QFrame *>(
      "frame_2", Qt::FindDirectChildrenOnly);
  QStackedWidget *wStacked = ui->stackedWidget_3;
  QButtonGroup *buttonGroup = new QButtonGroup(this);

  for (QPushButton *wBut : tabsButtonsFrame->findChildren<QPushButton *>(
           QString(), Qt::FindDirectChildrenOnly)) {
    wBut->setCheckable(true);
    buttonGroup->addButton(wBut);
    ui->MenuBtn->setCheckable(true);
  }

  // Check the first button

  tabsButtonsFrame
      ->findChild<QPushButton *>("HomeBtn", Qt::FindDirectChildrenOnly)
      ->setChecked(true);

  // Connect button group to stacked widget

  connect(buttonGroup,
          QOverload<QAbstractButton *>::of(&QButtonGroup::buttonClicked), this,
          [=]() {
            QString pageName =
                buttonGroup->checkedButton()->objectName().replace("Btn",
                                                                   "Page");
            QWidget *wPage = wStacked->findChild<QWidget *>(
                pageName, Qt::FindDirectChildrenOnly);
            wStacked->setCurrentWidget(wPage);
          });
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_MenuBtn_clicked()
{

    if (!ui->MenuBtn->isChecked())
        // Create a property animation object
       { QPropertyAnimation* animation = new QPropertyAnimation(ui->LeftMenuContainer, "maximumWidth");

        // Set the target value of the animation
        animation->setEndValue(50);

        // Set the duration of the animation in milliseconds
        animation->setDuration(500);

        // Start the animation
        animation->start();
        }
        else
        {QPropertyAnimation* animation = new QPropertyAnimation(ui->LeftMenuContainer, "maximumWidth");

            // Set the target value of the animation
            animation->setEndValue(129);

            // Set the duration of the animation in milliseconds
            animation->setDuration(500);

            // Start the animation
            animation->start();
            }


}



void MainWindow::on_SettingsBtn_clicked()
{
ui->CenterMenuContainer->hide() ;}
