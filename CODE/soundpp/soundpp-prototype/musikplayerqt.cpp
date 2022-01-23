#include "musikplayerqt.h"

#include <QCoreApplication>

MusikPlayer::MusikPlayerQt::MusikPlayerQt()
{
    m_playlist = new QMediaPlaylist();
    this->setPlaylist(m_playlist);
    setSongPath(QCoreApplication::applicationDirPath() + "/../../testsongs/01 - Sultans Of Swing.mp3");
    setMedia(songPath());
    setIsPlayling(false);
//    this->setMedia((/*QCoreApplication::applicationDirPath() + "/../../testsongs/01 - Sultans Of Swing.mp3"*/));
}


namespace MusikPlayer {

QUrl MusikPlayerQt::songPath() const
{
    return m_songPath;
}

void MusikPlayerQt::setSongPath(const QUrl &songPath)
{
    m_songPath = songPath;
}

void MusikPlayerQt::addToPlaylist(const QList<QUrl> &urls)
{

}

bool MusikPlayerQt::pressPlay()
{
    setIsPlayling(!isPlayling());
    qDebug() << "playing" << isPlayling();
    isPlayling() ? play() : pause();
    return m_isPlayling;
}



bool MusikPlayerQt::isPlayling() const
{
    return m_isPlayling;
}

void MusikPlayerQt::setIsPlayling(bool isPlayling)
{
    m_isPlayling = isPlayling;
}

}
