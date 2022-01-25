#include "soundppmanagement.h"

#include <QUrl>

namespace Management {

SoundppManagement::SoundppManagement(QObject *parent) : QObject(parent)
{
    dbc = new Database::DataBaseConnection();
    mpqt = new MusikPlayer::MusikPlayerQt();
    mdr = new MetaData::MetaDataFromFile();
    dm = new Model::DataManagement(dbc->getQueryModel_all());

    //musikplayer connection forwarding
    connect(mpqt, &MusikPlayer::MusikPlayerQt::durationChanged, this, &Management::SoundppManagement::durationChanged);
    connect(mpqt, &MusikPlayer::MusikPlayerQt::positionChanged, this, &Management::SoundppManagement::positionChanged);
}

QSqlQueryModel *SoundppManagement::getQueryModel_all()
{
//    return dbc->getQueryModel_all();
    dm->setAllSongs(dbc->getQueryModel_all()); //TODO:: update sql model from dbconnection
    return dm->getAllSongs();
}

//QSqlQueryModel *SoundppManagement::get_all_artists(){
//    return dbc->get_all_artists();
//}

bool SoundppManagement::droppedFile(QString filePath)
{
    MetaData::MetaDataItem mi = mdr->getMetaDataFromFilePath(filePath);
    dbc->insertMetaItem(mi);
}

void SoundppManagement::incrementPlayCount()
{

    QString songPath("C:/Users/Winny/Code_Local/Repositories/soundpp/CODE/soundpp/testsongs/01 - Sultans Of Swing.mp3");
    if(!mpqt->playedOnce()){
//        QString songPath = mpqt->songPath().toString();  // TODO::
        dbc->incrementPlayCount(songPath);
    }
}

bool SoundppManagement::pressPlay()
{
    incrementPlayCount();
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
