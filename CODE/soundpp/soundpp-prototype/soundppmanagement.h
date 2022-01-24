#ifndef SOUNDPPMANAGEMENT_H
#define SOUNDPPMANAGEMENT_H

#include <QObject>
#include <QUrl>
#include <QString>

#include "databaseconnection.h"
#include "musikplayerqt.h"
#include "metadatareader.h"
#include "metadataitem.h"


namespace Management {

class SoundppManagement : public QObject
{
    Q_OBJECT
private:
    Database::DataBaseConnection *dbc;
    MusikPlayer::MusikPlayerQt *mpqt;
    MetaData::MetaDataFromFile *mdr;

public:
    explicit SoundppManagement(QObject *parent = nullptr);
    // database get
    QSqlQueryModel *getQueryModel_all();

    //MetaData / database drop

    bool droppedFile(QString filePath);

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
