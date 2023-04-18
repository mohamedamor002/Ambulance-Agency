#ifndef AMBULANCE_H
#define AMBULANCE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class ambulance
{
    QString type,manufacturer,fueltype;
    int A_id,reg_number,year;
public:
    ambulance();
    ambulance(int ,int ,QString ,QString, int , QString);

    //getters
    QString gettype(QString type){return this->type=type;}
    QString getman(QString manufacturer){return this->manufacturer=manufacturer;}
    QString getfuel(QString fueltype){return this->fueltype=fueltype;}
    int getID(){return A_id;}
    int getreg(){return reg_number;}
    int getyear(){return year;}

    //setters
    void settype(QString type){this->type=type;}
    void setman(QString manufacturer){this->manufacturer=manufacturer;}
    void setfuel(QString fueltype){this->fueltype=fueltype;}
    void setID(int A_id){this->A_id=A_id;}
    void setreg(int reg_number){this->reg_number=reg_number;}
    void setyear(int year){this->year=year;}

    //student base features
    bool Create();
    bool Update();
    QSqlQueryModel * Read();
    QSqlQueryModel * Sort(const QString &);
    QSqlQueryModel * Search(int id);
    bool Delete(int);
};
#endif // AMBULANCE_H
