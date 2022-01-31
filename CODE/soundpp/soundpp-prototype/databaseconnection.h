#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>

#include "modelsong.h"


namespace Database {

class DataBaseConnection
{
public:
    DataBaseConnection();
    QSqlQueryModel* getQueryModel_all();
    void insertQuery(QSqlQuery qry);
    void insertSong(Model::Song song);
    void updateAllSongsModel();
    void incrementPlayCount(QString filePath);
    void deleteSong(QString filePath);


private:
    QSqlDatabase sqlitedb;
    QSqlQueryModel *allSongsQueryModel;
};

}
#endif // DATABASECONNECTION_H
