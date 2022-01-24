#ifndef SOUNDPPMANAGEMENT_H
#define SOUNDPPMANAGEMENT_H

#include <QObject>

#include "databaseconnection.h"
#include "musikplayerqt.h"


namespace Management {

class SoundppManagement : public QObject
{
    Q_OBJECT
private:
    Database::DataBaseConnection *dbc;
    MusikPlayer::MusikPlayerQt *mpqt;

public:
    explicit SoundppManagement(QObject *parent = nullptr);
    // database
    QSqlQueryModel *getQueryModel_all();

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
