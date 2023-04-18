#ifndef CALENDAR_H
#define CALENDAR_H
#include <QSqlQuery>
#include <QSqlQueryModel>
 #include <QDate>
#include <QTime>
#include <QPrinter>
#include <QPrintDialog>


class calendar
{  int idcl,idv;
    QDate dater;
    QTime Hour;





public:
    calendar(){}
    calendar (int ,QDate ,QTime ,int );
    //Getters
    QDate getdater(){return dater;}
    QTime getHour(){return Hour;}

   int getidv(){return idv;}
    int getidcalendar(){return idcl;}
    //Setters
    void setdater(QDate a){dater=a;}
    void setHour(QTime b){Hour=b;}

    void setidv(int d){idv=d;}
    void setidcalendar(int x){idcl=x;}
    //entete fcts
    bool add();
    void makecall();
    QSqlQueryModel *display();
    bool Delete(int);
    bool update(int ,QDate ,QTime ,int  );

};


#endif // CALENDAR_H
