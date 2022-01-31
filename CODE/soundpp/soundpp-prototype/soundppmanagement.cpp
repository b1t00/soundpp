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

QSqlQueryModel *SoundppManagement::get_all_artists_direct_from_database(){
    return dbc->get_all_artists();
}

QList<Model::Artist> SoundppManagement::create_and_get_artists(){
    return dm->create_and_get_artists();
}

QList<Model::Song> SoundppManagement::create_and_get_songs(){
    return dm->create_and_get_songs();
}


QSqlQueryModel *SoundppManagement::getQueryModel_all()
{
//  return dbc->getQueryModel_all();
    //dm->setAllSongs(dbc->getQueryModel_all()); //TODO:: update sql model from dbconnection
    qInfo() << "Moin test hier";
    return dm->getAllSongs();

}

QStringList *SoundppManagement::get_all_Interprets(){
    return dm->getAllInterprets();
}

//QSqlQueryModel *SoundppManagement::get_all_artists(){
//    return dbc->get_all_artists();
//}

Model::Song SoundppManagement::droppedFile(QString filePath)
{
    Model::Song song_to_add = mdr->getMetaDataFromFilePath(filePath);
//    dm->addSong(song_to_add);
    dbc->insertSong(song_to_add);
    return song_to_add; // goes back to ui, for songs model
}

void SoundppManagement::incrementPlayCount(QString songPath)
{
    if(!mpqt->playedOnce()){
//        QString songPath = mpqt->songPath().toString();  // TODO::
        dbc->incrementPlayCount(songPath);
    }
}

void SoundppManagement::deleteSong(QString filePath)
{
    dbc->deleteSong(filePath);
}

bool SoundppManagement::pressPlay()
{
//    if(!mpqt->isAudioAvailable()) return false;
    return mpqt->pressPlay();
}

void SoundppManagement::doubleclickPlay(QString songPath)
{
    mpqt->setSongPath(songPath);
    mpqt->setIsPlayling(true);
    mpqt->play();
//    pressPlay();
}


void SoundppManagement::setVolume(int volume)
{
    mpqt->setVolume(volume);
}

void SoundppManagement::setPosition(int position)
{
    mpqt->setPosition(position);

}

bool SoundppManagement::isAudioAvailable() const
{
    return mpqt->isAudioAvailable();
}

}
