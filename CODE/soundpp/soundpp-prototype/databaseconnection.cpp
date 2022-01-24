#include "databaseconnection.h"
#include <QList>
#include <QMessageBox>

Database::DataBaseConnection::DataBaseConnection()
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
                        songNr      INTEGER, \
                        artistName	TEXT, \
                        albumName	TEXT, \
                        labelName	TEXT, \
                        labelNr     TEXT, \
                        realeaseDate TEXT, \
                        addedDate	TEXT, \
                        fileFormat	TEXT, \
                        coverPath	TEXT, \
                        playCount   INTEGER, \
                        PRIMARY KEY(songPath) );");
        sqlitedb.close();

    } else {
//        QMessageBox::information(this,"Note connected", "Data Base Not Connected");
        qDebug() << "not connted";
    }


}

QSqlQueryModel* Database::DataBaseConnection::getQueryModel_all()
{
    bool open_success;
    open_success = sqlitedb.open();
    QSqlQueryModel *qm = new QSqlQueryModel();
    qInfo() << "db get query connected: " << open_success;
    qm->setQuery("SELECT * FROM songsTable");
    sqlitedb.close();
    return qm;
}

void Database::DataBaseConnection::insertQuery(QSqlQuery blub)
{
    this->sqlitedb.open();
    QSqlQuery qry;
    QString bla("testi224rewrew22");
    QString bla2("testi2");
    char numma = 41;
    QString sqerystring = "insert into songsTable (songPath, songName, songNr) values ('"+bla+"','"+bla2+"','"+numma+"')";
     QSqlQuery query;
    query.prepare("INSERT INTO songsTable (songPath, songName, songNr) "
                  "VALUES (:id, :name, :salary)");

    query.bindValue(":id", 1001);
    query.bindValue(":name", "Thad Beaumont");
    query.bindValue(":salary", numma);
//         qry.prepare(sqerystring);
//        qry.prepare(queryString);
        if(query.exec()){
            qInfo() << "data is saved";
        }
//    }
        this->sqlitedb.close();
}

void Database::DataBaseConnection::insertMetaItem(MetaData::MetaDataItem mi)
{
    this->sqlitedb.open();
    QSqlQuery qry;

    qry.prepare("INSERT INTO songsTable (songPath, songName, songNr, artistName, albumName, addedDate) "
                  "VALUES (:songPath, :songName, :songNr, :artistName, :albumName, :addedDate)");
    qry.bindValue(":songPath", mi.songPath());
    qry.bindValue(":songName", mi.songName());
    qry.bindValue(":songNr", mi.songNr());
    qry.bindValue(":artistName", mi.artistName());
    qry.bindValue(":albumName", mi.albumName());
    qry.bindValue(":addedDate", (QString::number(QDateTime::currentMSecsSinceEpoch()))); // Unix Epoche Time

    if(qry.exec()){
        qInfo() << "data is saved";
    }
    this->sqlitedb.close();
}




