#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>

#include "metadataitem.h"


namespace Database {

class DataBaseConnection
{
public:
    DataBaseConnection();
    QSqlQueryModel * getQueryModel_all();
    void insertQuery(QSqlQuery qry);
    void insertMetaItem(MetaData::MetaDataItem mi);
    void incrementPlayCount(QString filePath);


private:
    QSqlDatabase sqlitedb;
};

}
#endif // DATABASECONNECTION_H
