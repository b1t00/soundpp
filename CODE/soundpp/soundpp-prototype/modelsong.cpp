#include "modelsong.h"

namespace Model{
Song::Song()
{

}

Song::Song(QString title):

    m_title(title)
{
}


QString Song::getTitle() const
{
    return title;
}

void Song::setTitle(const QString &value)
{
    title = value;
}

QString Song::getSongPath() const
{
    return m_songPath;
}

void Song::setSongPath(const QString &songPath)
{
    m_songPath = songPath;
}

QString Song::getArtistName() const
{
    return m_artistName;
}

void Song::setArtistName(const QString &artistName)
{
    m_artistName = artistName;
}

QString Song::getLabelName() const
{
    return m_labelName;
}

void Song::setLabelName(const QString &labelName)
{
    m_labelName = labelName;
}

QString Song::getAddedTime() const
{
    return m_addedTime;
}

void Song::setAddedTime(const QString &addedTime)
{
    m_addedTime = addedTime;
}

int Song::getPlayCount() const
{
    return m_playCount;
}

void Song::setPlayCount(int playCount)
{
    m_playCount = playCount;
}
}
