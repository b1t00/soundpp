#include "musikplayer.h"

mp::MusikPlayer::MusikPlayer(QObject *parent) : QObject(parent)
{
    this->qmp = new QMediaPlayer(this);
    this->song_path = QCoreApplication::applicationDirPath() + "/../../testsongs/01 - Sultans Of Swing.mp3";
    this->qmp->setMedia(this->song_path);
    this->playing = false;

    QObject::connect(qmp, &QMediaPlayer::durationChanged, this, &MusikPlayer::durationChanged); //connection wird weitergeleitet
    QObject::connect(qmp, &QMediaPlayer::positionChanged, this, &MusikPlayer::positionChanged); //connection wird weitergeleitet
}

bool mp::MusikPlayer::play_song()
{
    if(!playing){
        this->qmp->play();
    } else {
        this->qmp->pause();
    }

//    !playing ? mp->play() : mp->pause();

    playing = !playing;
    return playing;
}

bool mp::MusikPlayer::set_song_path(QString spath){
    this->song_path = spath;

    //    durationChanged(30);
}

void mp::MusikPlayer::setVolume(int volume)
{
    this->qmp->setVolume(volume);
}

void mp::MusikPlayer::setPosition(int position)
{
    this->qmp->setPosition(position);
}

//void mp::MusikPlayer::positionChanged(qint64 position)
//{

//}

//void mp::MusikPlayer::durationChanged(qint64 duration){
//    this->qmp->durationChanged(duration);
//};
//void mp::MusikPlayer::positionChanged(qint64 position){

//};



