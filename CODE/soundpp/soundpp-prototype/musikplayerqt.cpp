#include "musikplayerqt.h"

#include <QCoreApplication>

MusikPlayer::MusikPlayerQt::MusikPlayerQt()
{
    m_playlist = new QMediaPlaylist();
//    m_playlist->setPlaybackMode(QMediaPlaylist::AutoPla);
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
//    #elif LINUX // dont work for ubuntu
//    crossPlatformFile = "file://" + songPath.toString();
//    #else
//    #error "We don't support your system or version yet, sorry..."
    #endif
    m_songPath = crossPlatformFile;
//    qDebug() << "songpath: " << crossPlatformFile;
    setMedia(QUrl(crossPlatformFile));
}

void MusikPlayerQt::addToQueue(QUrl url)
{
    m_playlist->addMedia(url);
    setPlaylist(m_playlist);

}

bool MusikPlayerQt::pressPlay()
{
    if(!m_playedOnce) m_playedOnce = true;
    setIsPlayling(!isPlayling());
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
