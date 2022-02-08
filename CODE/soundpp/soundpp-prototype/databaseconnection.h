#ifndef DATABASECONNECTION_H
#define DATABASECONNECTION_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <QDebug>

#include "modelsong.h"
#include "playlist.h"


namespace Database {

class DataBaseConnection
{
public:
    DataBaseConnection( );
    QList<Model::Song> *get_and_create_all_Songs();
    QList<Model::Playlist> *get_and_create_all_Playlists();
    void insertSong(Model::Song song);
    void insertPlaylist(Model::Playlist playlist);
    Model::Song editSong(Model::Song edited_song);
    void updateAllSongsModel();
    void updateAllPlaylistsModel();
    int incrementPlayCount(QString filePath);
    bool deleteSong(QString filePath);
    bool deletePlaylist(int playlistID);


private:
    QSqlDatabase sqlitedb;
    QSqlQueryModel *allSongsQueryModel;
    QSqlQueryModel *allPlaylistsQueryModel;
    QList<Model::Song> *m_all_songs;
    QList<Model::Playlist> *m_all_playlists;

//    QList<Model::Song> m_all_songs;
};

}
#endif // DATABASECONNECTION_H
