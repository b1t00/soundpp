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
    QSqlQueryModel* getQueryModel_all();
    QSqlQueryModel* get_all_artists();
    void insertQuery(QSqlQuery qry);
    void insertMetaItem(MetaData::MetaDataItem mi);
    void incrementPlayCount(QString filePath);
    void deleteSong(QString filePath);


private:
    QSqlDatabase sqlitedb;
};

}
#endif // DATABASECONNECTION_H
