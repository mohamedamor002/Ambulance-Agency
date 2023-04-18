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


    bool on_lineEditManufacEquip_editingFinished();

    void on_comboBoxFilterEquip_activated(const QString &arg1);


    void on_lineEditSearchEquip_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Equipment Etmp ;

    void  setEquipmentInterface() ;
    void setWindowInterface() ;
    void setWindowAmbulance() ;
    void  Equipment_CRUD() ;
    void Ambulance_CRUD() ;
    Equipment GetEquipmentFromForm() ;
     QString FilterEquip;
     QString SearchEquip;
};
#endif // MAINWINDOW_H
