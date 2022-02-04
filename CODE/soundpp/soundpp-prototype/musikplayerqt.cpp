#include "musikplayerqt.h"

#include <QCoreApplication>

MusikPlayer::MusikPlayerQt::MusikPlayerQt()
{
    m_playlist = new QMediaPlaylist();
    this->setPlaylist(m_playlist);
    setIsPlayling(false);
}


namespace MusikPlayer {

bool MusikPlayerQt::playedOnce() const
{
    return m_playedOnce;
}

QUrl MusikPlayerQt::songPath() const
{
    return m_songPath;
}

void MusikPlayerQt::setSongPath(const QUrl &songPath)
{
    m_playedOnce = false;
    QString crossPlatformFile;
    crossPlatformFile = "file://" + songPath.toString();
    #ifdef WIN32
    crossPlatformFile = songPath.toString();
    qDebug() << "Windows filepath:" << crossPlatformFile;
//    #elif LINUX
//    crossPlatformFile = "file://" + songPath.toString();
//    qDebug() << "Ubuntu filepath:" << crossPlatformFile;
//    #else
//    #error "We don't support your system or version yet, sorry..."
    #endif
    m_songPath = crossPlatformFile;
    qDebug() << "songpath: " << crossPlatformFile;
    setMedia(QUrl(crossPlatformFile));
}

void MusikPlayerQt::addToPlaylist(const QList<QUrl> &urls)
{



}

bool MusikPlayerQt::pressPlay()
{

    if(!m_playedOnce) m_playedOnce = true;

    setIsPlayling(!isPlayling());
//    qDebug() << "playing" << isPlayling();
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
