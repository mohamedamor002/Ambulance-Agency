#include "calendar.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork>
#include <QUrl>
#include <QUrlQuery>
#include <iostream>

using namespace std;

calendar::calendar(int  ,QDate D,QTime H,int c)
{
    QSqlQuery query;
    query.exec("select MAX(ID_CL) from calendar");
      if(query.next())
      {
      int last_id = query.value(0).toInt();
      idcl=last_id+1;
       dater=D;
       Hour=H;
       idv=c;
      }
}
void calendar::makecall() {

    const QString SID = "AC8d0c73e087c1675ddd136d2452bf63d3";
    const QString AUTH = "96e69db2cf5ce16eaa2e9ccf0be8ff06";

    const QString API = "Messages";
    QUrl url("https://api.twilio.com/2010-04-01/Accounts/" + SID + "/" + API +
             ".json");
    QUrlQuery query;
    query.addQueryItem("From", "+15076901655");
    query.addQueryItem("To", "+21624902219");
    query.addQueryItem("Body", "Your reservation is added to the Database succesfully!");

    QNetworkRequest request(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    const QByteArray authorization =
        "Basic " + (SID + ":" + AUTH).toUtf8().toBase64();
    request.setRawHeader("Authorization", authorization);

    QSslConfiguration sslConfig = QSslConfiguration::defaultConfiguration();
    sslConfig.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(sslConfig);
    QNetworkAccessManager manager;
    QNetworkReply *reply =
        manager.post(request, query.toString(QUrl::FullyEncoded).toUtf8());
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() != QNetworkReply::NoError) {
      qWarning() << "Error making call:" << reply->errorString();
      // reply->rawHeaderPairs();
    } else {
      qDebug() << "Call successful!";
    }

    // auto response = reply->readAll();
    // qInfo().noquote() << QJsonDocument::fromJson(response).toJson(
    //     QJsonDocument::Indented);
    // qInfo().noquote() << QJsonDocument::fromJson(response);

    reply->deleteLater();
  }


bool calendar::add(){
    QSqlQuery query;
    calendar c;
    QString res1 = QString::number(idcl);
    query.prepare("insert into CALENDAR (ID_CL,ID_V,DATER,Hour)" "values (:id, :cin, :D, :H )");
    query.bindValue(":id",idcl);
     query.bindValue(":D",dater);
      query.bindValue(":H",Hour);
       query.bindValue(":cin",idv);
       bool success = query.exec();
          if (success) {
              c.makecall();
          }
          return success;
}
class DateQueryModel : public QSqlQueryModel {
public:
    QVariant data(const QModelIndex &item, int role) const override {
        if (role == Qt::DisplayRole && item.column() == 2) { // If it's the "DATER" column
            QDateTime dateTime = QSqlQueryModel::data(item).toDateTime(); // Get the date/time value from the model
            return dateTime.date().toString(Qt::ISODate); // Convert the date/time value to a date string without the time component
        } else if (role == Qt::DisplayRole && item.column() == 3) { // If it's the "HOUR" column
            QDateTime dateTime = QSqlQueryModel::data(item).toDateTime(); // Get the date/time value from the model
            return dateTime.time().toString(Qt::ISODate); // Convert the date/time value to a time string without the date component
        }
        return QSqlQueryModel::data(item, role); // Return the data from the base class for all other roles and columns
    }
};

    QSqlQueryModel * calendar::display(){
        DateQueryModel *m = new DateQueryModel();

        m->setQuery("SELECT * from calendar");
        m->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_CL"));
        m->setHeaderData(1,Qt::Horizontal,QObject::tr("ID_V"));

        m->setHeaderData(2,Qt::Horizontal,QObject::tr("DATER"));
        m->setHeaderData(3,Qt::Horizontal,QObject::tr("HOUR"));

        return m;
}
    bool calendar::Delete(int idcl){
        QSqlQuery query;
        QString res=QString::number(idcl);
        query.prepare("Delete from calendar where ID_CL= :id");
        query.bindValue(":id",res);
        return query.exec();

    }

   /* bool calendar::update(int id,QDate D,QTime H,int cin)
    {
        QSqlQuery query;
        QString res = QString::number(id);
        query.prepare("Update calendar SET DATE_R= :DATE_R ,Hour = :HEURE ,ID_V= :CIN_C  where ID_CL= :ID_CL");
        query.bindValue(":ID_CL",res);
        query.bindValue(":DATE_R",D);
        query.bindValue(":HEURE",H);
        query.bindValue(":CIN_C",cin);


        return query.exec();
    }*/
