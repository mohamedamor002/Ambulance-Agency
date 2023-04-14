#include "connection.h"

connection::connection()
{

}
bool  connection::createConnection()
{
    db= QSqlDatabase::addDatabase("QODBC")  ;
    bool test= false ;
    db.setDatabaseName("Source_project2A") ;
    db.setUserName("amor");
    db.setPassword("7894") ;
    if(db.open()) test=true   ;
    return test  ;
    return true ;
}
void connection::closeConnection(){db.close();}
