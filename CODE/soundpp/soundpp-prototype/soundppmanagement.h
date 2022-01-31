#ifndef SOUNDPPMANAGEMENT_H
#define SOUNDPPMANAGEMENT_H

#include <QObject>
#include <QUrl>
#include <QString>

#include "databaseconnection.h"
#include "musikplayerqt.h"
#include "metadatareader.h"

#include "modeldatamanagement.h"
#include "artist.h"

namespace Management {

class SoundppManagement : public QObject
{
    Q_OBJECT
private:
    Database::DataBaseConnection *dbc;
    MusikPlayer::MusikPlayerQt *mpqt;
    MetaData::MetaDataFromFile *mdr;
    Model::DataManagement *dm;

public:
    explicit SoundppManagement(QObject *parent = nullptr);
    // database get
    QSqlQueryModel *getQueryModel_all();
    QSqlQueryModel get_all_artists();
    QStringList* get_all_Interprets();
    QList<Model::Artist> create_and_get_artists();
    QList<Model::Song> create_and_get_songs();
    QList<Model::Song> filtered_songs_by_artist(QString artist);

    //MetaData / database drop

    Model::Song droppedFile(QString filePath);
    void incrementPlayCount();
    void deleteSong(QString filePath);

    //musikplayerqt
    bool pressPlay();
    void doubleclickPlay(QString songPath);
    void setVolume(int volume);
    void setPosition(int position);
    void on_songs_tableView_doubleClicked(const QModelIndex &index);

signals:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
//    void songDoubleClicked(const QModelIndex &index);

};

}
#endif // SOUNDPPMANAGEMENT_H
