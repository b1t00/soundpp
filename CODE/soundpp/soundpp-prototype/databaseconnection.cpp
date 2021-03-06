#include "databaseconnection.h"


#include <QList>
#include <QMessageBox>

Database::DataBaseConnection::DataBaseConnection()
{
    sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/musicDataBase.db";
    sqlitedb.setDatabaseName(dbPath);
    allSongsQueryModel = new QSqlQueryModel();
    allPlaylistsQueryModel = new QSqlQueryModel();
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

//        allSongsQueryModel->setQuery("CREATE TABLE playlistTable ( /
//                        playlistName TEXT, \
//                        playlistGenre TEXT, \
//                        );");
        sqlitedb.close();

    } else {
//        QMessageBox::information(this,"Note connected", "Data Base Not Connected");
        qDebug() << "not connted";
    }

    m_all_songs = new QList<Model::Song>();

    if(sqlitedb.open()){
        qInfo() << "db playlist auch";

        allPlaylistsQueryModel->setQuery("CREATE TABLE playlistTable ( \
                                            playlistName TEXT \
                                            playlistID INTEGER);");

            sqlitedb.close();


       m_all_playlists = new QList<Model::Playlist>();


    }else {
        qInfo() << "Doch nicht connected";
    }

}


QList<Model::Song>* Database::DataBaseConnection::get_and_create_all_Songs(){
    bool open_success;
    open_success = sqlitedb.open();

    QSqlQuery qry;
    qInfo() << "db get query connected: " << open_success;
    qry.prepare("SELECT * FROM songsTable");
    qry.exec();
    allSongsQueryModel->setQuery(qry);
    sqlitedb.close();


    for(int i = 0; i < allSongsQueryModel->rowCount(); i++){
        Model::Song song;
        song.setTitle(allSongsQueryModel->record(i).value("songName").toString());
        song.setSongPath(allSongsQueryModel->record(i).value("songPath").toString());
        song.setArtistName(allSongsQueryModel->record(i).value("artistName").toString());
        song.setAlbumName(allSongsQueryModel->record(i).value("albumName").toString());
        song.setAlbumNr(allSongsQueryModel->record(i).value("songNr").toInt());
        song.setAddedTime(allSongsQueryModel->record(i).value("addedDate").toString());
        song.setPlayCount(allSongsQueryModel->record(i).value("playCount").toInt());
        m_all_songs->append(song);
    }

    return m_all_songs;

}

QList<Model::Playlist>* Database::DataBaseConnection::get_and_create_all_Playlists() {
    bool open_success;
    open_success = sqlitedb.open();

    QSqlQuery qry;
    qInfo() << "db get query connected: " << open_success;
    qry.prepare("SELECT * FROM playlistTable");
    qry.exec();
    allPlaylistsQueryModel->setQuery(qry);
    sqlitedb.close();

    for(int i = 0; i < allPlaylistsQueryModel->rowCount(); i++){
        Model::Playlist playlist;
        playlist.setPlaylistName(allPlaylistsQueryModel->record(i).value("playlistName").toString());
        playlist.setPlaylistID(allPlaylistsQueryModel->record(i).value("playlistID").toInt());
        m_all_playlists->append(playlist);
        }

    return m_all_playlists;

}

void Database::DataBaseConnection::insertPlaylist(Model::Playlist playlist){

    this->sqlitedb.open();

    QSqlQuery qry;

    qry.prepare("INSERT INTO playlistTable (playlistName, playlistID) VALUES (:playlistName, :playlistID)" );

    qry.bindValue(":playlistName", playlist.getPlaylistName());
    qry.bindValue(":playlistID", playlist.getPlaylistID());
    qry.exec();

    this->sqlitedb.close();

    updateAllPlaylistsModel();



}

void Database::DataBaseConnection::insertSong(Model::Song song)
{
    this->sqlitedb.open();
    QSqlQuery qry;

    qry.prepare("INSERT INTO songsTable (songPath, songName, songNr, artistName, albumName, addedDate, playCount) "
                "VALUES (:songPath, :songName, :songNr, :artistName, :albumName, :addedDate, 0)");
    qry.bindValue(":songPath", song.getSongPath());
    qry.bindValue(":songName", song.getTitle());
    qry.bindValue(":songNr", song.getAlbumNr());
    qry.bindValue(":albumName", song.getAlbumName());
    qry.bindValue(":artistName", song.getArtistName());
    qry.bindValue(":addedDate", song.getAddedTime());
    qry.bindValue(":playCount", song.getPlayCount());
    qry.exec();
//    if(allSongsQueryModel.exec()){
//        qInfo() << "data is saved";
//    }
    this->sqlitedb.close();
    updateAllSongsModel(); //?
}

Model::Song Database::DataBaseConnection::editSong(Model::Song edited_song)
{
    this->sqlitedb.open();
    QSqlQuery qry;
    qry.prepare("UPDATE songsTable SET songName = :songName, artistName = :artistName, albumName = :albumName, songNr = :songNr  WHERE songPath = :songPath ");
//    qDebug() << edited_song.getSongPath();
    qry.bindValue(":songName", edited_song.getTitle());
    qry.bindValue(":artistName", edited_song.getArtistName());
    qry.bindValue(":albumName", edited_song.getAlbumName());
    qry.bindValue(":songNr", edited_song.getAlbumNr());
    qry.bindValue(":songPath", edited_song.getSongPath());
//    qry.bindValue(":addedDate", edited_song.getAddedTime());
    if(!qry.exec()){
        qDebug("Warning!! No Song Editing");
        return edited_song;
    };
    qry.clear();
    qry.prepare("SELECT * FROM songsTable WHERE songPath = (:songPath)");
    qry.bindValue(":songPath", edited_song.getSongPath());
    if(!qry.exec()){
        qDebug("Warning!! No Song Editing 2");
        return edited_song;
    };
    allSongsQueryModel->setQuery(qry);
    Model::Song song_from_db;
    song_from_db.setSongPath(allSongsQueryModel->record(0).value("songPath").toString());
    song_from_db.setTitle(allSongsQueryModel->record(0).value("songName").toString());
    song_from_db.setArtistName(allSongsQueryModel->record(0).value("artistName").toString());
    song_from_db.setAlbumName(allSongsQueryModel->record(0).value("albumName").toString());
    song_from_db.setAlbumNr(allSongsQueryModel->record(0).value("songNr").toInt());
    song_from_db.setAddedTime(allSongsQueryModel->record(0).value("addedDate").toString());
    song_from_db.setPlayCount(allSongsQueryModel->record(0).value("playCount").toInt());
    this->sqlitedb.close();
    return song_from_db;
}

void Database::DataBaseConnection::updateAllSongsModel()
{
    sqlitedb.open();
    allSongsQueryModel->setQuery("SELECT * FROM songsTable");
    sqlitedb.close();
}

void Database::DataBaseConnection::updateAllPlaylistsModel()
{
    sqlitedb.open();
    allPlaylistsQueryModel->setQuery("SELECT * FROM playlistTable");
    sqlitedb.close();
}

int Database::DataBaseConnection::incrementPlayCount(QString filePath)
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
    if(playCount > -99){
        qry.prepare("UPDATE songsTable SET playCount = (:playCount) WHERE songPath = (:songPath)");
        qry.bindValue(":playCount", ++playCount);
        qry.bindValue(":songPath", filePath);

        if (!qry.exec()){
            qDebug() << "NOT incemented playcound";
        }
    }
    qry.prepare("SELECT playCount FROM songsTable WHERE songPath = (:songPath)");
    qry.bindValue(":songPath", filePath);
    int newPlayCount = -99;
    if (qry.exec()){
       if (qry.next()){
//           qDebug() << "qry value " << qry.value(0).toInt();
           newPlayCount = qry.value(0).toInt();
       }
    }
    this->sqlitedb.close();
    return newPlayCount;
}

bool Database::DataBaseConnection::deleteSong(QString filePath)
{
    this->sqlitedb.open();
    QSqlQuery qry;
    qry.prepare("DELETE from songsTable WHERE songPath = (:songPath)");
    qry.bindValue(":songPath", filePath);
    if (qry.exec()){
        return true;
    }
    return false;
}


bool Database::DataBaseConnection::deletePlaylist(int playlistID){
    this->sqlitedb.open();
    QSqlQuery qry;
    qry.prepare("DELETE from playlistTable WHERE playlistID = (:playlistID)");
    qry.bindValue(":playlistID", playlistID);
    if(qry.exec()){
        return true;
    }
    return false;
}



