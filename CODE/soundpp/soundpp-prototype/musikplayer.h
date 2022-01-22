#ifndef MUSIKPLAYER_H
#define MUSIKPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QDebug>
#include <QCoreApplication>

namespace mp {

class MusikPlayer : public QObject
{
    Q_OBJECT
public:
    explicit MusikPlayer(QObject *parent = nullptr);
    bool play_song();
    bool set_song_path(QString spath);
    void setVolume(int volume);
    void setPosition(int position);
signals:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);

private:
    QMediaPlayer *qmp;
    QUrl song_path;
    bool playing;
};

}

#endif // MUSIKPLAYER_H
