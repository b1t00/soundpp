#ifndef METADATAITEM_H
#define METADATAITEM_H

#include <QString>


namespace MetaData {

class MetaDataItem
{
private:
    QString m_songPath;
    QString m_songName;
    int m_songNr; // the listing number in an album or single
    QString m_artistName;
    QString m_albumName;

public:
    MetaDataItem();
    MetaDataItem(QString songPath, QString songName, int songNr, QString artistName, QString albumName);
    QString songPath() const;
    void setSongPath(const QString &songPath);
    QString songName() const;
    void setSongName(const QString &songName);
    int songNr() const;
    void setSongNr(int songNr);
    QString artistName() const;
    void setArtistName(const QString &artistName);
    QString albumName() const;
    void setAlbumName(const QString &albumName);
};

}
#endif // METADATAITEM_H
