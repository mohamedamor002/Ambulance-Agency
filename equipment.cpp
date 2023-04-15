#include "equipment.h"


Equipment::Equipment(int id,QString name ,int serial ,QString manufacturer,QString purchase ,QString expire,QString status,QString info,int quantity)

{

    this->eid =  id  ;
    this->serial_number=serial ;
    this->quantity=quantity;
    this->name=name ;
   this->manufacturer=manufacturer ;
    this->status=status;
    this->info=info;
    this->de=  expire ;
    this->dp = purchase ;


}
bool Equipment::Create()
{


    QSqlQuery query ;
    QString res2 = QString::number(serial_number);
    QString res3 = QString::number(quantity);

    //prepare
    query.prepare("insert into EQUIPMENT(NAME,SERIALNUMBER,MANUFACTURER,PDATE,EDATE,STATUS,INFO,QUANTITY)""values(:n,:s,:m,:p,:e,:st,:in,:q)");
    //bind

    query.bindValue(":n",name);
    query.bindValue(":s",res2);
    query.bindValue(":m",manufacturer);
    query.bindValue(":p",de);
    query.bindValue(":e",dp);
    query.bindValue(":st",status);
    query.bindValue(":in",info);
    query.bindValue(":q",quantity);
    return query.exec() ;
}


bool Equipment::Delete(int id)
{
    QSqlQuery query  ;
    QString res= QString::number(id) ;
    query.prepare("Delete from EQUIPMENT where E_ID= :id");
    query.bindValue(":id",res);
    return query.exec() ;

}

QSqlQueryModel * Equipment::read()
{
    QSqlQueryModel * model = new QSqlQueryModel() ;
    model->setQuery("SELECT * from EQUIPMENT") ;
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Equipment"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Serial Number"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Manufacturer"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Purchase Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Expire Date"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Status"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Infor"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Quantity"));
return model   ;
}
bool Equipment::Update()
{


    QSqlQuery query ;
    QString res = QString::number(eid) ;
    QString res2 = QString::number(serial_number);
    QString res3 = QString::number(quantity);

query.prepare("UPDATE EQUIPMENT SET NAME=:n,SERIALNUMBER=:se,MANUFACTURER=:ma,PDATE=:pd,EDATE=:ed,STATUS=:sta,INFO=:info,QUANTITY=:q WHERE E_ID=:i")  ;
query.bindValue(":i",eid );
query.bindValue(":n",name) ;
query.bindValue(":se",res2) ;
query.bindValue(":ma",manufacturer) ;
query.bindValue(":pd",de) ;
query.bindValue(":ed",dp) ;
query.bindValue(":sta",status) ;
query.bindValue(":info",info) ;
query.bindValue(":q",res3) ;




return query.exec() ;
}


QSqlQueryModel * Equipment::search(QString s)
{

QSqlQueryModel *model= new QSqlQueryModel() ;

QSqlQuery query ;

query.prepare("SELECT * FROM EQUIPMENT WHERE NAME like '%"+s+"%'");
query.bindValue(":name", "%" + s + "%");

//query.prepare("SELECT * FROM EQUIPMENT WHERE NAME like =:name");
//query.bindValue(":name", "%" + s + "%");


query.exec();
model->setQuery(query);
model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("Equipment Name"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Serial Number"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Manufacturer"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Purchase Date"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Expire Date"));
model->setHeaderData(6, Qt::Horizontal, QObject::tr("Status"));
model->setHeaderData(7, Qt::Horizontal, QObject::tr("Infor"));
model->setHeaderData(8, Qt::Horizontal, QObject::tr("Quantity"));
return model ;
}

QChartView * Equipment::equipment_stat()
{
  int oxygen=0 ;
  int  defi =0 ;
  int heart =0  ;
  int   intra=0     ;
  int spine=0   ;
  int neck=0   ;
   int  suction=0 ;
          int  stretcher=0 ;
          int  first =0 ;
          int blanket=0 ;
          int prote=0 ;
QSqlQuery query ;
query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","Oxygen Tank");
query.exec();
oxygen = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","Defibrillator");
query.exec();
defi = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","Heart monitor");
query.exec();
heart = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","IV");
query.exec();
intra = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","Spine Board");
query.exec();
spine = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","Neck Collar");
query.exec();
neck = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","Suction device");
query.exec();
suction = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","Stretcher ramp");
query.exec();
stretcher = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","First aid kit");
query.exec();
first = query.next() ? query.value(0).toInt() : 0;


query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","Blankets");
query.exec();
blanket = query.next() ? query.value(0).toInt() : 0;

query.prepare("SELECT SUM(QUANTITY) from EQUIPMENT WHERE NAME=:p");
query.bindValue(":p","gloves and gowns");
query.exec();
prote = query.next() ? query.value(0).toInt() : 0;

QBarSet *oxygenSet = new QBarSet("Oxygen Tank");
    *oxygenSet << oxygen;
    QBarSet *defiSet = new QBarSet("Defibrillator");
    *defiSet << defi;
    QBarSet *heartSet = new QBarSet("Heart monitor");
    *heartSet << heart;
    QBarSet *intraSet = new QBarSet("IV");
    *intraSet << intra;
    QBarSet *spineSet = new QBarSet("Spine Board");
    *spineSet << spine;
    QBarSet *neckSet = new QBarSet("Neck Collar");
    *neckSet << neck;
    QBarSet *suctionSet = new QBarSet("Suction device");
    *suctionSet << suction;
    QBarSet *stretcherSet = new QBarSet("Stretcher ramp");
    *stretcherSet << stretcher;
    QBarSet *firstSet = new QBarSet("First aid kit");
    *firstSet << first;
    QBarSet *blanketSet = new QBarSet("Blankets");
    *blanketSet << blanket;
    QBarSet *proteSet = new QBarSet("gloves and gowns");
    *proteSet << prote;
    QBarSeries *series = new QBarSeries();
        series->append(oxygenSet);
        series->append(defiSet);
        series->append(heartSet);
        series->append(intraSet);
        series->append(spineSet);
        series->append(neckSet);
        series->append(suctionSet);
        series->append(stretcherSet);
        series->append(firstSet);
        series->append(blanketSet);
        series->append(proteSet);
        QChart *chart = new QChart();
            chart->addSeries(series);
            /*QBarCategoryAxis *axisX = new QBarCategoryAxis();
            axisX->append({"Oxygen Tank", "Defibrillator", "Heart monitor", "IV", "Spine Board", "Neck Collar", "Suction device", "Stretcher ramp", "First aid kit", "Blankets", "Gloves and gowns"});
            chart->addAxis(axisX, Qt::AlignBottom);
            series->attachAxis(axisX);*/
            QValueAxis *axisY = new QValueAxis();
            axisY->setLabelFormat("%i");
           // axisY->setRange(0, 10); // adjust the range to your data
            chart->addAxis(axisY, Qt::AlignLeft);
            series->attachAxis(axisY);
            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);

            // set the chart view as the central widget of the main window
            //setCentralWidget(chartView);
            return chartView ;
}


QSqlQueryModel * Equipment::read_sortby(QString option)
{

    QSqlQueryModel * model = new QSqlQueryModel() ;

    model->setQuery("SELECT * from EQUIPMENT ORDER BY "+option) ;

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Equipment Name"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Serial Number"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Manufacturer"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Purchase Date"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Expire Date"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Status"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Infor"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Quantity"));
return model   ;

}
QSqlQueryModel * Equipment:: search3(QString s,QString p)

{QSqlQueryModel *model= new QSqlQueryModel() ;
    QSqlQuery query ;

    query.prepare("SELECT * FROM EQUIPMENT WHERE NAME like '%"+s+"%' ORDER BY "+p);
    query.bindValue(":name", "%" + s + "%");




    query.exec();
//    qDebug() << query.executedQuery();

    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Equipment Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Serial Number"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Manufacturer"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Purchase Date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Expire Date"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Status"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Infor"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Quantity"));
    return model ;



}

