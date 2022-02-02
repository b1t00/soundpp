#ifndef MODELDATAMANAGEMENT_H
#define MODELDATAMANAGEMENT_H

#include <QMap>
#include <QObject>
#include <QSqlQueryModel>
#include <QSqlRecord>
#include <QString>
#include "artist.h"
#include "modelsong.h"

namespace Model {

class DataManagement : public QObject
{
    Q_OBJECT
private:
    //QStringList artists;
      QList<Model::Song> m_all_songs;
//    QList<Song> m_songs();
//    QMap<Song> m_allSongs();
//    QMap<Song> *m_all;
public:
    explicit DataManagement(QObject *parent = nullptr);
    explicit DataManagement(QList<Model::Song> all_songs, QObject *parent = nullptr);
    QStringList* getAllInterprets();
    QList<Model::Song> get_all_songs() const;
    void setAllSongs(QList<Model::Song> allSongs);
    QList<Model::Song> songs();
    QList<Model::Song> filtered_songs_by_artist(QString artist);
    QList<Model::Song> search_result(QString search);
    bool deleteSong(QString filePath);
    bool insertSong(Model::Song song_to_add);




signals:

};

}
#endif // MODELDATAMANAGEMENT_H
