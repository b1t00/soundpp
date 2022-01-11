#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>



class DataBaseConnection
{
public:
    DataBaseConnection();
    QSqlQueryModel * getQueryModel_all();


private:
    QSqlDatabase sqlitedb;
};

#endif // DATABASECONNECTION_H
