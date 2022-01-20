#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>


namespace dbc {

class DataBaseConnection
{
public:
    DataBaseConnection();
    QSqlQueryModel * getQueryModel_all();
    void insertQuery(QString queryString);


private:
    QSqlDatabase sqlitedb;
};

}
#endif // DATABASECONNECTION_H
