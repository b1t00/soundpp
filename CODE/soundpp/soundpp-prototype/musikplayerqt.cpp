#include "musikplayerqt.h"

#include <QCoreApplication>

MusikPlayer::MusikPlayerQt::MusikPlayerQt()
{
    m_playlist = new QMediaPlaylist();
//    m_playlist->addMedia(QUrl("C:/Users/Winny/Music/Musik/testmusik/[1977] Lust For Life/04 - The Passenger.mp3"));
//    m_playlist->addMedia(QUrl("C:/Users/Winny/Music/Musik/testmusik/[1977] Lust For Life/05 - Tonight.mp3"));
//    m_playlist->addMedia(QUrl("C:/Users/Winny/Music/Musik/testmusik/[1977] Lust For Life/02 - Sixteen.mp3"));
//    m_playlist->setPlaybackMode(QMediaPlaylist::AutoPla);
//    m_playlist->()
    this->setPlaylist(m_playlist);
    setIsPlayling(false);
//    playlist()->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
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

void MusikPlayerQt::addToQueue(QUrl url)
{
    qDebug() << "add media " << url;
//    playlist()->addMedia(url);
    m_playlist->addMedia(url);
    setPlaylist(m_playlist);

}

bool MusikPlayerQt::pressPlay()
{
//    m_playlist->setCurrentIndex(0);
    if(!m_playedOnce) m_playedOnce = true;

    setIsPlayling(!isPlayling());
    qDebug() << "playing" << isPlayling();
    isPlayling() ? play() : pause();
    return m_isPlayling;
}

void MusikPlayerQt::playNext()
{
    qDebug() << "playlist current index" << m_playlist->currentIndex();
    qDebug() << "playlist mext index" << m_playlist->nextIndex();
    m_playlist->setCurrentIndex(m_playlist->nextIndex());
    play();
//    playlist()->next();

//    m_playlist->next();
//    m_playlist->next();
//    playlist()->
//    play();
//    next();
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
