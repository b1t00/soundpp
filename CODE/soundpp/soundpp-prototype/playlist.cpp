#include "playlist.h"
namespace Model {

Playlist::Playlist(){}

Playlist::Playlist(QString name):
    playlistName(name)
{

}

int Playlist::getPlaylistID() const
{
    return playlistID;
}

void Playlist::setPlaylistID(int value)
{
    playlistID = value;
}

QList<Model::Song> Playlist::getSongs_of_playlist() const
{
    return songs_of_playlist;
}

void Playlist::setSongs_of_playlist(const QList<Model::Song> &value)
{
    songs_of_playlist = value;
}

void Playlist::add_song_to_playlist(Song song)
{
    songs_of_playlist.append(song);

}



QString Playlist::getPlaylistName() const
{
    return playlistName;
}

void Playlist::setPlaylistName(const QString &value)
{
    playlistName = value;
}


}
