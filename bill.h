#ifndef BILL_H
#define BILL_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class bill
{
    QString fname,lname,phone,type,insurance , value;
    int b_id,h_id,p_id,state ;
    //float value ;
public:
    bill();
   bill(QString, QString,QString ,QString,QString , int ,int , int ,int,QString) ;

    //getters

    QString getFname(){return fname;}
    QString getLname(){return lname;}
    QString getphone(){return phone ;}
    QString gettype(){return type;}
    QString getinsurance(){return insurance;}
    int getB_ID(){return b_id ;}
    int getH_ID(){return h_id;}
    int getP_ID(){return p_id;}
   QString getvalue(){return value;}

    //setters

    void setfname(QString n){ fname=n;}
    void setlname(QString n){ lname=n;}
    void setinsurance(QString s){insurance=s;}
    void settype(QString t){type=t;}
    void setphone(QString e){phone=e;}
    void setB_ID(int p){phone=p ;}
    void setH_ID(int nb){h_id=nb;}
    void setP_ID(int nb){p_id=nb;}
    void setvalue(QString i ){value =i ;}

    //

    bool create() ;
    QSqlQueryModel *read () ;
    bool Delete(int) ;
    bool Update() ;
   // QSqlQueryModel * recherche(QString rech);





};

#endif // BILL_H
