#include "databaseconnection.h"


#include <QList>
#include <QMessageBox>

Database::DataBaseConnection::DataBaseConnection()
{
    sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/musicDataBase.db";
    sqlitedb.setDatabaseName(dbPath);
    allSongsQueryModel = new QSqlQueryModel();
    if(sqlitedb.open()){
//        QSqlQueryModel *qm = new QSqlQueryModel();
        qInfo() << "db connected";
        allSongsQueryModel->setQuery("CREATE TABLE songsTable ( \
                        songPath	TEXT, \
                        songName	TEXT, \
                        songNr      INTEGER, \
                        artistName	TEXT, \
                        albumName	TEXT, \
                        genre       TEXT, \
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

QSqlQueryModel* Database::DataBaseConnection::get_all_artists(){


    bool open_success;
    open_success = sqlitedb.open();
    QSqlQueryModel *artists = new QSqlQueryModel();
    artists->setQuery("SELECT artistName FROM songsTable");
    qInfo()<< "db läuft " << open_success;
    sqlitedb.close();
    return artists;


}



QSqlQueryModel* Database::DataBaseConnection::getQueryModel_all()
{
    bool open_success;
    open_success = sqlitedb.open();
//    QSqlQueryModel *qm = new QSqlQueryModel();
//    AllSongsSqlModel *qm = new AllSongsSqlModel();

    qInfo() << "db get query connected: " << open_success;
    QSqlQuery qry;
    qry.prepare("SELECT * FROM songsTable");
    qry.exec();
    allSongsQueryModel->setQuery(qry);
    sqlitedb.close();

//   for(int i = 0; i < qm->rowCount(); i++){
//       if(qm->record(i).value("artistName") == "Blumentopf"){
//        qInfo() << qm->record(i).value("artistName");
//           qDebug() << qm->record(i).value("songName").toString();
//    }

//   }
        return allSongsQueryModel;

}

void Database::DataBaseConnection::insertQuery(QSqlQuery qry) // TODO:: currently no functionality
{
//    this->sqlitedb.open();
//    QSqlQuery qry;
//    QString bla("testi224rewrew22");
//    QString bla2("testi2");
//    char numma = 41;
//    QString sqerystring = "insert into songsTable (songPath, songName, songNr) values ('"+bla+"','"+bla2+"','"+numma+"')";
//     QSqlQuery query;
//    query.prepare("INSERT INTO songsTable (songPath, songName, songNr) "
//                  "VALUES (:id, :name, :salary)");

//    query.bindValue(":id", 1001);
//    query.bindValue(":name", "Thad Beaumont");
//    query.bindValue(":salary", numma);
//        if(query.exec()){
//            qInfo() << "data is saved";
//        }
////    }
//        this->sqlitedb.close();
}

void Database::DataBaseConnection::insertSong(Model::Song song)
{
    this->sqlitedb.open();
    QSqlQuery qry;

    qry.prepare("INSERT INTO songsTable (songPath, songName, songNr, artistName, albumName, addedDate, playCount) "
                  "VALUES (:songPath, :songName, :songNr, :artistName, :albumName, :addedDate, 0)");
    qry.bindValue(":songPath", song.getSongPath());
    qry.bindValue(":songName", song.getTitle());
    qry.bindValue(":albumName", song.getAlbumName());
    qry.bindValue(":artistName", song.getArtistName());
    qry.bindValue(":addedDate", song.getAddedTime());
    qry.bindValue(":playCount", song.getPlayCount());
    qry.exec();

//    allSongsQueryModel->setQuery(qry);
//    allSongsQueryModel->

//    if(allSongsQueryModel.exec()){
//        qInfo() << "data is saved";
//    }
    this->sqlitedb.close();
    updateAllSongsModel();
}

void Database::DataBaseConnection::updateAllSongsModel()
{
    sqlitedb.open();
    allSongsQueryModel->setQuery("SELECT * FROM songsTable");
    sqlitedb.close();
}

void Database::DataBaseConnection::incrementPlayCount(QString filePath)
{
    this->sqlitedb.open();
    QSqlQuery qry;
    qry.prepare("SELECT playCount FROM songsTable WHERE songPath = (:songPath)");
    qry.bindValue(":songPath", filePath);
    int playCount = -99;
    if (qry.exec()){
       if (qry.next()){
//           qDebug() << "qry value " << qry.value(0).toInt();
           playCount = qry.value(0).toInt();
       }
    }
//    playCount++;
    if(playCount > -99){
        qry.prepare("UPDATE songsTable SET playCount = (:playCount) WHERE songPath = (:songPath)");
        qry.bindValue(":playCount", ++playCount);
        qry.bindValue(":songPath", filePath);

        if (!qry.exec()){
            qDebug() << "NOT incemented playcound";
        }
    }
    this->sqlitedb.close();
}

void Database::DataBaseConnection::deleteSong(QString filePath)
{
    this->sqlitedb.open();
    QSqlQuery qry;
    qry.prepare("DELETE from songsTable WHERE songPath = (:songPath)");
    qry.bindValue(":songPath", filePath);
    if (qry.exec()){
        qInfo() << "Deleted: " << filePath;
    }
}




