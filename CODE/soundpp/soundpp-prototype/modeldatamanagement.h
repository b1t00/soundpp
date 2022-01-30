#ifndef MODELDATAMANAGEMENT_H
#define MODELDATAMANAGEMENT_H

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include "artist.h"
#include "modelsong.h"

namespace Model {

class DataManagement : public QObject
{
    Q_OBJECT
private:
    QSqlQueryModel  *m_allSongs;
    //QStringList artists;
    QList<Artist> m_artists();
    QList<Song> m_songs();
public:
    explicit DataManagement(QObject *parent = nullptr);
    explicit DataManagement(QSqlQueryModel  *allSongs, QObject *parent = nullptr);
    QStringList* getAllInterprets();
    QSqlQueryModel *getAllSongs() const;
    void setAllSongs(QSqlQueryModel *allSongs);
    QList<Artist> create_and_get_artists();
    QList<Song> create_and_get_songs();
    QList<Artist> artists();
    QList<Song> songs();

signals:

};

}
#endif // MODELDATAMANAGEMENT_H
