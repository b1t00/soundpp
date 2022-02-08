#ifndef MODELDATAMANAGEMENT_H
#define MODELDATAMANAGEMENT_H

#include <QMap>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include <QUrl>
#include "modelsong.h"
#include "playlist.h"

namespace Model {

class DataManagement : public QObject
{
    Q_OBJECT
private:
    //DELETE
    //QStringList artists;
      QList<Model::Song> *m_all_songs;
      QList<Model::Playlist> *m_all_playlists;
//    QList<Song> m_songs();
//    QMap<Song> m_allSongs();
//    QMap<Song> *m_all;
public:
    explicit DataManagement(QObject *parent = nullptr);
    explicit DataManagement(QList<Model::Song> *all_songs, QList<Model::Playlist> *all_playlists, QObject *parent = nullptr);
    QList<Model::Song> get_all_songs() const;
    QList<Model::Playlist> get_all_playlists();
    void setAllSongs(QList<Model::Song> *allSongs);

    QList<Model::Song> songs();
    QList<Model::Song> filtered_songs_by_artist(QString artist);
    QList<Model::Song> filtered_songs_by_album(QString album);
    QList<Model::Song> search_result(QString search);
    void add_songs_for_playlist(Model::Song song, QString playlistName);

    QList<QString> allAlbums();
    QList<QString> allArtists();

    Model::Song randomSong();

    bool deleteSong(QString filePath);
    bool insertSong(Model::Song song_to_add);
    bool editSong(Model::Song song_from_db);
    bool insert_playlist(Model::Playlist new_playlist);
    bool containsSongPath(QString songPath);
    bool deletePlaylist(int playlistID);






signals:

};

}
#endif // MODELDATAMANAGEMENT_H
