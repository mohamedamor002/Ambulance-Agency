#include "mainwindow.h"

#include <QApplication>
#include "connection.h"
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c  ;
    bool test=c.createConnection() ;
    MainWindow w;
    w.showFullScreen();
    if(test)
    {w.show();
        QMessageBox::information(nullptr,QObject::tr("Database is open"),
                                 QObject::tr("Connection successful.\n Click cancel to exist"),QMessageBox::Cancel);

    }
    else
        QMessageBox::information(nullptr,QObject::tr("Database is not open"),
                                 QObject::tr("Connection failed.\n Click cancel to exist"),QMessageBox::Cancel);




    return a.exec();
}
