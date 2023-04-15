#include "hospital.h"
hospital:: hospital(){}
hospital:: hospital(QString name, QString adress,QString speciality ,QString type,QString email,QString s_id,int phone, int nb_beds,int nb_patients,int  id )
{

this->id=id ;
this->name=name ;
this -> adress=adress ;
this->speciality =speciality ;
this->type=type ;
this->email=email ;
this-> phone=phone ;
this ->nb_beds=nb_beds ;
this->nb_patients=nb_patients ;
this->s_id=s_id ;

}
bool hospital:: create()
{
    QSqlQuery  query;

   QString id1 = QString::number(id);
   QString phone1 = QString::number(phone);
   QString nb_beds1 = QString::number(nb_beds);
   QString nb_patients1= QString::number(nb_patients);

    //prepare() takes the query as a parameter to prepare it for execution
    query.prepare("insert into hospital (H_ID, PHONE,S_ID,NBR_BEDS,NBR_PATIENTS,ADDRESS,TYPE,HNAME,SPECIALITY,EMAIL) values (:H_ID, :PHONE,:S_ID,:NBR_BEDS,:NBR_PATIENTS,:ADDRESS,:TYPE,:HNAME,:SPECIALITY,:EMAIL)");

    // Creating variables
    query.bindValue(":H_ID",id1);
    query.bindValue(":PHONE",phone1);
    query.bindValue(":S_ID",s_id);
    query.bindValue(":NBR_BEDS",nb_beds1);
    query.bindValue(":NBR_PATIENTS",nb_patients1);
    query.bindValue(":ADDRESS",adress);
    query.bindValue(":TYPE",type);
    query.bindValue(":HNAME",name);
    query.bindValue(":SPECIALITY",speciality);
    query.bindValue(":EMAIL",email);

    return query.exec();
}

bool hospital::Delete(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from hospital where H_ID= :id");

    query.bindValue(":id",res);

    return  query.exec();

}

QSqlQueryModel * hospital::read()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from hospital");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("H_ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("HNAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("ADRESS"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PHONE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("SPECIALITY"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("TYPE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("NBR_BEDS"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("NBR_PATIENTS"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("S_ID"));

    return  model;
}

bool hospital::Update()
{


   QString id1 = QString::number(id);
   QString phone1 = QString::number(phone);
   QString nb_beds1 = QString::number(nb_beds);
   QString nb_patients1= QString::number(nb_patients);
   QSqlQuery  query;
    //prepare() takes the query as a parameter to prepare it for execution
   query.prepare("UPDATE hospital SET PHONE=:phone, S_ID=:s_id, NBR_BEDS=:nb_beds, NBR_PATIENTS=:nb_patients, ADDRESS=:adress, TYPE=:type, HNAME=:name, SPECIALITY=:speciality, EMAIL=:email  WHERE H_ID=:id ");




    // Creating variables
    query.bindValue(":id",id);
    query.bindValue(":phone",phone1);
    query.bindValue(":s_id",s_id);
    query.bindValue(":nb_beds",nb_beds1);
    query.bindValue(":nb_patients",nb_patients1);
    query.bindValue(":adress",adress);
    query.bindValue(":type",type);
    query.bindValue(":name",name);
    query.bindValue(":speciality",speciality);
    query.bindValue(":email",email);
    return query.exec();


}




