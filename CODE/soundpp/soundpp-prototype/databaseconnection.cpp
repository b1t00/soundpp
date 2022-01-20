#include "databaseconnection.h"
#include <QMessageBox>

dbc::DataBaseConnection::DataBaseConnection()
{
    this->sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/musicDataBase.db";
    sqlitedb.setDatabaseName(dbPath);

    if(sqlitedb.open()){
        QSqlQueryModel *qm = new QSqlQueryModel();
        qInfo() << "db connected";
        qm->setQuery("CREATE TABLE songsTable ( \
                        songPath	TEXT, \
                        songName	TEXT, \
                        artistName	TEXT, \
                        albumName	TEXT, \
                        labelName	TEXT, \
                        labelNr     TEXT, \
                        realeaseDate	INTEGER, \
                        addedOn	INTEGER, \
                        fileFormat	TEXT, \
                        coverPath	TEXT, \
                        playCount       INTEGER, \
                        PRIMARY KEY(songPath) );");
        sqlitedb.close();

    } else {
//        QMessageBox::information(this,"Note connected", "Data Base Not Connected");
        qDebug() << "not connted";
    }


}

QSqlQueryModel* dbc::DataBaseConnection::getQueryModel_all()
{
    bool open_success;
    open_success = sqlitedb.open();
    QSqlQueryModel *qm = new QSqlQueryModel();
    qInfo() << "db get query connected: " << open_success;
    qm->setQuery("SELECT * FROM songsTable");
    sqlitedb.close();
    return qm;
}

void dbc::DataBaseConnection::insertQuery(QString queryString)
{
    this->sqlitedb.open();
    QSqlQuery qry;
//    qInfo() << (erster_wert == NULL);
//    if(erster_wert == NULL){
//        qry.prepare("insert into tabelle1 (name,album) values ('"+zweiter_wert+"','"+dritter_wert+"')");
//        if(qry.exec()){
//            qInfo() << "data id 0 is saved";
//        }
//    } else {

//        qry.prepare("insert into tabelle1 (id,name,album) values ('"+erster_wert+"','"+zweiter_wert+"','"+dritter_wert+"')");
        qry.prepare(queryString);
        if(qry.exec()){
            qInfo() << "data is saved";
        }
//    }
    this->sqlitedb.close();
}




