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



QString Playlist::getPlaylistName() const
{
    return playlistName;
}

void Playlist::setPlaylistName(const QString &value)
{
    playlistName = value;
}


}
