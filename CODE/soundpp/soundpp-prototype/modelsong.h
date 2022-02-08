#ifndef MODELSONG_H
#define MODELSONG_H
#include <QString>



namespace Model {
class Song
{
public:
    Song();
    Song( QString songPath, QString title, QString artistName, QString albumName,
          int labelNr, QString addedTime, int m_playCount);
    // simple copy of song
    Song( QString songPath, QString title, QString artistName, QString albumName );

    QString getSongPath() const;
    void setSongPath(const QString &songPath);
    QString getTitle() const;
    void setTitle(const QString &value);
    QString getArtistName() const;
    void setArtistName(const QString &artistName);
    QString getAlbumName() const;
    void setAlbumName(const QString &albumName);
    int getAlbumNr() const;
    void setAlbumNr(int albumNr);
    QString getLabelName() const;
    void setLabelName(const QString &labelName);
    QString getLabelNr() const;
    void setLabelNr(const QString &labelNr);
    QString getAddedTime() const;
    void setAddedTime(const QString &addedTime);
    int getPlayCount() const;
    void setPlayCount(int playCount);

    friend bool compareByAlbumNr(const Model::Song& lhs, const Model::Song& rhs);


private:

    QString m_songPath;
    QString m_title;
    QString m_artistName;
    QString m_albumName;
    int m_albumNr;
    QString m_labelName;
    QString m_labelNr;
    QString m_addedTime;
    int m_playCount;

};

//using namespace albumNr_compare
static bool compareByAlbumNr(const Model::Song& lhs, Model::Song& rhs) // func for sorting by pages count
{
    return lhs.getAlbumNr() < rhs.getAlbumNr();
}
}

#endif // MODELSONG_H

