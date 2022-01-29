#ifndef SOUNDPPMANAGEMENT_H
#define SOUNDPPMANAGEMENT_H

#include <QObject>
#include <QUrl>
#include <QString>

#include "databaseconnection.h"
#include "musikplayerqt.h"
#include "metadatareader.h"
#include "metadataitem.h"

#include "datamanagement.h"
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
    QSqlQueryModel *get_all_artists_direct_from_database();
    QStringList* get_all_Interprets();
    QList<Model::Artist> create_and_get_artists();
    QList<Model::Song> create_and_get_songs();

    //MetaData / database drop

    bool droppedFile(QString filePath);
    void incrementPlayCount();

    //musikplayerqt
    bool pressPlay();
    void setVolume(int volume);
    void setPosition(int position);

signals:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);

};

}
#endif // SOUNDPPMANAGEMENT_H
