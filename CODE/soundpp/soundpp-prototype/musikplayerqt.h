#ifndef MUSIKPLAYERQT_H
#define MUSIKPLAYERQT_H

#include <QMediaPlayer>
#include <QMediaPlaylist>

namespace MusikPlayer {
/*
* we want to substitute the QMediaPlayer
* by other libaries like Essentia in the future
* to be able to implement more functionalities
*/

class MusikPlayerQt : public QMediaPlayer
{
private:
    bool m_isPlayling;
    bool m_playedOnce;
    QUrl m_songPath;
    /*
     * m_playlist is not in use
     * we decided for implementing it on our own
     * to be independet from QMediaPlayer
     */
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
