#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);

    ui->SizeGrip->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_CloseBtn_clicked()
{
    close();

}

void MainWindow::on_RestoreBtn_clicked()
{
isMaximized() ? showNormal() :showMaximized() ;
}

void MainWindow::on_MinimizeBtn_clicked()
{
    setWindowState(Qt::WindowState::WindowMinimized) ;
}
