#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QPropertyAnimation>
#include "equipment.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_AddEquipBtn_clicked();

private:
    Ui::MainWindow *ui;
    Equipment Etmp ;

    void  setEquipmentInterface() ;
    void setWindowInterface() ;
    void  addEquipment() ;
};
#endif // MAINWINDOW_H
