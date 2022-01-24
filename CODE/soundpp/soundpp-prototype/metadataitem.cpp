#include "metadataitem.h"

namespace MetaData {

QString MetaDataItem::songPath() const
{
    return m_songPath;
}

void MetaDataItem::setSongPath(const QString &songPath)
{
    m_songPath = songPath;
}

QString MetaDataItem::songName() const
{
    return m_songName;
}

void MetaDataItem::setSongName(const QString &songName)
{
    m_songName = songName;
}

int MetaDataItem::songNr() const
{
    return m_songNr;
}

void MetaDataItem::setSongNr(int songNr)
{
    m_songNr = songNr;
}

QString MetaDataItem::artistName() const
{
    return m_artistName;
}

void MetaDataItem::setArtistName(const QString &artistName)
{
    m_artistName = artistName;
}

QString MetaDataItem::albumName() const
{
    return m_albumName;
}

void MetaDataItem::setAlbumName(const QString &albumName)
{
    m_albumName = albumName;
}

MetaDataItem::MetaDataItem()
{

}

MetaDataItem::MetaDataItem(QString songPath, QString songName, int songNr, QString artistName, QString albumName):
    m_songPath(songPath), m_songName(songName), m_songNr(songNr), m_artistName(artistName), m_albumName(albumName)
{
}
}
