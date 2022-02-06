#include "playlist.h"
namespace Model {


Playlist::Playlist(){}

Playlist::Playlist(QString name):
    playlistName(name)
{

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
