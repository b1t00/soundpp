#ifndef MODELSONG_H
#define MODELSONG_H
#include <QString>



namespace Model {

class Song
{
public:
    Song();
    Song(QString title);
    QString title;

    QString getTitle() const;
    void setTitle(const QString &value);
    QString getSongPath() const;
    void setSongPath(const QString &songPath);

    QString getArtistName() const;
    void setArtistName(const QString &artistName);

    QString getLabelName() const;
    void setLabelName(const QString &labelName);

    QString getAddedTime() const;
    void setAddedTime(const QString &addedTime);

    int getPlayCount() const;
    void setPlayCount(int playCount);

private:

    QString m_songPath;
    QString m_artistName;
    QString m_title;
    QString m_labelName;
    QString m_addedTime;
    int m_playCount;

};
}

#endif // MODELSONG_H
