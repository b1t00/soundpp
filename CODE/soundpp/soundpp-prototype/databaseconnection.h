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
    QList<Model::Song> get_and_create_all_Songs();
    void insertQuery(QSqlQuery qry);
    void insertSong(Model::Song song);
    void updateAllSongsModel();
    void incrementPlayCount(QString filePath);
    bool deleteSong(QString filePath);


private:
    QSqlDatabase sqlitedb;
    QSqlQueryModel *allSongsQueryModel;
    QList<Model::Song> m_all_songs;
};

}
#endif // DATABASECONNECTION_H
