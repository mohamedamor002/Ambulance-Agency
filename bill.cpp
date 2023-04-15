#include "bill.h"
bill:: bill(){}
bill:: bill(QString fname , QString lname ,QString insurance ,QString phone,QString type , int h_id ,int b_id , int p_id ,int state,QString  value )
{

this->h_id=h_id ;
this->fname=fname ;
this->lname=lname ;
this->insurance= insurance ;
this->type= type ;
this-> phone=phone ;
this ->state=state ;
this->b_id=b_id ;
this->p_id=p_id ;
    this ->value=value ;

}
bool bill:: create()
{
   QSqlQuery  query;

   QString b_id1 = QString::number(b_id);
   QString h_id1 = QString::number(h_id);
   QString p_id1 = QString::number(p_id);
   QString state1 = QString::number(state);
  // QString value1= QString::number(value);

    //prepare() takes the query as a parameter to prepare it for execution
    query.prepare("insert into BILL (B_ID,FNAME,LNAME,PHONE_PATIENT,EMER_TYPE,A_ID,INSURANCE,BILL_STATE,VALUE,H_ID) values (:B_ID,:FNAME,:LNAME,:PHONE_PATIENT,:EMER_TYPE,:A_ID,:INSURANCE,:BILL_STATE,:VALUE,:H_ID)");

    // Creating variables
    query.bindValue(":B_ID",b_id1);
    query.bindValue(":FNAME",fname);
    query.bindValue(":LNAME",lname);
    query.bindValue(":PHONE_PATIENT",phone);
    query.bindValue(":EMER_TYPE",type);
    query.bindValue(":A_ID",p_id1);
    query.bindValue(":INSURANCE",insurance);
    query.bindValue(":BILL_STATE",state1);
    query.bindValue(":VALUE",value );
    query.bindValue(":H_ID",h_id1);

    return query.exec();
}





QSqlQueryModel * bill::read()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from bill");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("B_ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("FNAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("LNAME"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PHONE_PATIENT"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("EMER_TYPE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("A_ID"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("INSURANCE"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("BILL_STATE"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("VALUE"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("H_ID"));

    return  model;
}
bool bill::Delete(int id)
{
    QSqlQuery query;
    QString res=QString::number(id);
    query.prepare("Delete from bill where B_ID= :id");

    query.bindValue(":id",res);

    return  query.exec();

}




bool bill::Update()
{

    QSqlQuery  query;

    QString b_id1 = QString::number(b_id);
    QString h_id1 = QString::number(h_id);
    QString p_id1 = QString::number(p_id);
    QString state1 = QString::number(state);
   // QString value1= QString::number(value);

     //prepare() takes the query as a parameter to prepare it for execution
     query.prepare("Update  BILL set  B_ID=:B_ID,FNAME=:FNAME,LNAME=:LNAME,PHONE_PATIENT=:PHONE_PATIENT,EMER_TYPE=:EMER_TYPE,A_ID=:A_ID,INSURANCE=:INSURANCE,BILL_STATE=:BILL_STATE,VALUE=:VALUE,H_ID=:H_ID  WHERE B_ID=:B_ID");

     // Creating variables
     query.bindValue(":B_ID",b_id1);
     query.bindValue(":FNAME",fname);
     query.bindValue(":LNAME",lname);
     query.bindValue(":PHONE_PATIENT",phone);
     query.bindValue(":EMER_TYPE",type);
     query.bindValue(":A_ID",p_id1);
     query.bindValue(":INSURANCE",insurance);
     query.bindValue(":BILL_STATE",state1);
     query.bindValue(":VALUE",value);
     query.bindValue(":H_ID",h_id1);

     return query.exec();




//   query.prepare("UPDATE hospital SET PHONE=:phone, S_ID=:s_id, NBR_BEDS=:nb_beds, NBR_PATIENTS=:nb_patients, ADDRESS=:adress, TYPE=:type, HNAME=:name, SPECIALITY=:speciality, EMAIL=:email  WHERE H_ID=:id ");


}



