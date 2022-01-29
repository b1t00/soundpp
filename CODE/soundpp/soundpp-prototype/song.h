#ifndef SONG_H
#define SONG_H
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
private:

    QString m_title;
    };
}

#endif // SONG_H
