#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    ui->SizeGrip->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    connect(ui->CloseBtn, &QPushButton::clicked, this, [this]() { close(); });
    connect(ui->RestoreBtn, &QPushButton::clicked, this,
            [this]() { isMaximized() ? showNormal() : showMaximized(); });
    connect(ui->MinimizeBtn, &QPushButton::clicked, this,
            [this]() { setWindowState(Qt::WindowState::WindowMinimized); });

}

MainWindow::~MainWindow() 
{
  delete ui;
}
