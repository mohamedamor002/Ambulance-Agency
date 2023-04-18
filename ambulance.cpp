#include "ambulance.h"

ambulance::ambulance(){}
ambulance::ambulance(int A_id,int reg_number,QString t, QString man, int year, QString fueltype)
{
  this->A_id=A_id;
  this->reg_number=reg_number;
  this->type=t;
  this->manufacturer=man;
  this->year=year;
  this->fueltype=fueltype;
}
bool ambulance::Create()
{
    QSqlQuery query;
    QString id = QString::number(A_id);
    QString y = QString::number(year);
    QString reg = QString::number(reg_number);

    query.prepare("INSERT INTO Ambulance (A_ID, REG_NUMBER, TYPE, MANUFACTURER, YEAR, FUELTYPE)" "VALUES (:A_id, :reg_number, :type, :manufacturer, :year, :fueltype)");

    query.bindValue(":A_id",id);
    query.bindValue(":reg_number",reg);
    query.bindValue(":type",type);
    query.bindValue(":manufacturer",manufacturer);
    query.bindValue(":year",y);
    query.bindValue(":fueltype",fueltype);

    return query.exec();
}
bool ambulance::Update()
{



    QString id = QString::number(A_id);
    QString y = QString::number(year);
    QString reg = QString::number(reg_number);
    QSqlQuery qry;
    qry.prepare("UPDATE Ambulance SET REG_NUMBER=:reg,TYPE=:type,MANUFACTURER=:manufacturer,YEAR=:year,FUELTYPE=:fueltype WHERE A_ID=:id");
    qry.bindValue(":id", id);
    qry.bindValue(":reg", reg);
    qry.bindValue(":type", type);
    qry.bindValue(":manufacturer", manufacturer);
    qry.bindValue(":year", y);
    qry.bindValue(":fueltype", fueltype);

    return qry.exec();
}
bool ambulance::Delete(int A_id)
{
    QSqlQuery query;
    QString id=QString::number(A_id);

    query.prepare("DELETE FROM Amublance WHERE A_ID= :A_id");
    query.bindValue(":id",id);
    return query.exec();
}

QSqlQueryModel * ambulance::Read()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Ambulance");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("A_id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("reg_number"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("manufacturer"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("year"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("fueltype"));
    return model;
}
QSqlQueryModel * ambulance::Sort(const QString &arg1){

    QSqlQueryModel *model = new QSqlQueryModel();
        QString query;

        if (arg1 == "Date of Manufacturing") {
            query = "SELECT * FROM AMBULANCE ORDER BY YEAR ";
        } else if (arg1 == "Fuel type") {
            query = "SELECT * FROM AMBULANCE ORDER BY FUELTYPE ";
        } else if (arg1 == "Model") {
            query = "SELECT * FROM AMBULANCE ORDER BY MANUFACTURER ";
        }

        model->setQuery(query);
        return model;
}
QSqlQueryModel * ambulance::Search(int id){
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM AMBULANCE WHERE A_ID = " + QString::number(id));
    return model;
}
