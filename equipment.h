#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QBarSet>
#include <QBarSeries>
#include <QChart>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QChartView>
#include <QDate>


using namespace QtCharts;


class Equipment
{
    QString  name,manufacturer,status,info ,de,dp;
    int eid,serial_number,quantity;

public:
    Equipment(){};
    Equipment(int,QString,int,QString,QString,QString,QString,QString,int);
    //Getters
    QString getname(){ return name ; } ;
    QString getmanufacturer(){return manufacturer ;} ;
    QString getstatus() {return status;}
    QString getinfo(){return  info ;} ;
    int getid(){return eid;};
    int getserial(){return serial_number;};
    int getquantity(){return quantity;};
    QString getdatep(){return de;};
    QString getdatee(){return de ;};
//Setters
    void setname(QString n){name=n;};
    void setmanufacturer(QString m){manufacturer=m;};
    void setstatus(QString s){status=s;} ;
    void setinfo(QString i){info=i;};
    void setid(int i){eid=i;};
    void setserial(int s){serial_number=s;};
    void setquantity(int q){quantity=q;};
    void setdatee(QString d){de=d;};
    void setdatep(QString d){dp=d ;};
    //Equipments base features
    bool Create() ;
    QSqlQueryModel * read();
    QSqlQueryModel * read_sortby(QString) ;
    bool Delete(int id);
    bool Update()  ;
    QSqlQueryModel * search(QString s) ;
    QSqlQueryModel * search3(QString s,QString p) ;


    QChartView * equipment_stat() ;

};

#endif // EQUIPMENT_H
