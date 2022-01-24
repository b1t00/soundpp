#include "soundppmanagement.h"

namespace Management {

SoundppManagement::SoundppManagement(QObject *parent) : QObject(parent)
{
    dbc = new Database::DataBaseConnection();
    mpqt = new MusikPlayer::MusikPlayerQt();
    mdr = new MetaData::MetaDataFromFile();

    //musikplayer connection forwarding
    connect(mpqt, &MusikPlayer::MusikPlayerQt::durationChanged, this, &Management::SoundppManagement::durationChanged);
    connect(mpqt, &MusikPlayer::MusikPlayerQt::positionChanged, this, &Management::SoundppManagement::positionChanged);
}

QSqlQueryModel *SoundppManagement::getQueryModel_all()
{
    return dbc->getQueryModel_all();
}

bool SoundppManagement::droppedFile(QString filePath)
{
//    QString queryString = mdr->getMetaDataFromFilePath(filePath);
    MetaData::MetaDataItem mi = mdr->getMetaDataFromFilePath(filePath);
//    qDebug() << queryString;
    dbc->insertMetaItem(mi);
}

bool SoundppManagement::pressPlay()
{
    return mpqt->pressPlay();
}

void SoundppManagement::setVolume(int volume)
{
    mpqt->setVolume(volume);
}

void SoundppManagement::setPosition(int position)
{
    mpqt->setPosition(position);

}

}
