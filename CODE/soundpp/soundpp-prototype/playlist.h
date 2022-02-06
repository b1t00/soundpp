#ifndef PLAYLIST_H
#define PLAYLIST_H
#include <QString>

namespace Model {


class Playlist
{
public:
    Playlist();
    Playlist(QString playlistName);

    QString playlistName;


    QString getPlaylistName() const;
    void setPlaylistName(const QString &value);

};
}
#endif // PLAYLIST_H
