#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QString>
#include "modelsong.h"

namespace Model {


class Playlist
{
public:
    Playlist();
    Playlist(QString playlistName);

    QString playlistName;
    int playlistID;

    QList<Model::Song> songs_of_playlist;



    QString getPlaylistName() const;
    void setPlaylistName(const QString &value);

    int getPlaylistID() const;
    void setPlaylistID(int value);



    QList<Model::Song> getSongs_of_playlist() const;
    void setSongs_of_playlist(const QList<Model::Song> &value);

    void add_song_to_playlist(Model::Song song);

private:
    QString m_playlistName;
    int m_playlistID;



};
}
#endif // PLAYLIST_H
