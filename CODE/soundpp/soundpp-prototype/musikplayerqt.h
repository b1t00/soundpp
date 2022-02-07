#ifndef MUSIKPLAYERQT_H
#define MUSIKPLAYERQT_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace MusikPlayer {


class MusikPlayerQt : public QMediaPlayer
{
private:
    bool m_isPlayling;
    bool m_playedOnce;
    QUrl m_songPath;
    QMediaPlaylist *m_playlist = nullptr;

public:
    MusikPlayerQt();
    bool isPlayling() const;
    void setIsPlayling(bool isPlayling);

    QUrl songPath() const;
    void setSongPath(const QUrl &songPath);

    void addToQueue(QUrl url);

    bool pressPlay();

    bool playedOnce() const;

};

}
#endif // MUSIKPLAYERQT_H
