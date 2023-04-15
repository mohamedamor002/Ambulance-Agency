#ifndef HOSPITAL_H
#define HOSPITAL_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
class hospital
{
    QString name,adress,speciality ,type,email, s_id;
    int phone ,nb_beds, nb_patients, id;
public:
    hospital();
    hospital(QString, QString,QString ,QString,QString ,QString , int ,int , int ,int) ;

    //getters

    QString getname(){return name;}
    QString getadress(){return adress;}
    QString getspeciality(){return speciality;}
    QString gettype(){return type;}
    QString getemail(){return email;}
    int getphone(){return phone ;}
    int getnb_beds(){return nb_beds;}
     int getnb_patients(){return nb_patients;}
   QString gets_id(){return s_id ;}
    int getId(){return id ;}

    //setters

    void setname(QString n){ name=n;}
    void setadress(QString a){adress=a;}
    void setspeciality(QString s){speciality=s;}
    void settype(QString t){type=t;}
    void setemail(QString e){email=e;}
    void setphone(int p){phone=p ;}
    void setnb_beds(int nb){nb_beds=nb;}
    void setnb_patients(int nb){nb_patients=nb;}
    void sets_id(int i){ s_id=i ;}
    void setId(int i ){id =i ;}

    //

    bool create() ;
    QSqlQueryModel *read () ;
    bool Delete(int) ;
    bool Update() ;
   // QSqlQueryModel * recherche(QString rech);





};

#endif // HOSPITAL_H
