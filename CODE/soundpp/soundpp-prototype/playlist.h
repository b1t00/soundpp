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
    int playlistID;
    int increment = 0;


    QString getPlaylistName() const;
    void setPlaylistName(const QString &value);

    int getPlaylistID() const;
    void setPlaylistID(int value);

private:
    QString m_playlistName;
    int m_playlistID;
};
}
#endif // PLAYLIST_H
