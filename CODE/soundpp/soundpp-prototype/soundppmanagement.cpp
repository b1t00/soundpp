#include "soundppmanagement.h"

#include <QUrl>

namespace Management {

SoundppManagement::SoundppManagement(QObject *parent) : QObject(parent)
{
    dbc = new Database::DataBaseConnection();
    mpqt = new MusikPlayer::MusikPlayerQt();
    mdr = new MetaData::MetaDataFromFile();
    dm = new Model::DataManagement(dbc->get_and_create_all_Songs());

    //musikplayer connection forwarding
    connect(mpqt, &MusikPlayer::MusikPlayerQt::durationChanged, this, &Management::SoundppManagement::durationChanged);
    connect(mpqt, &MusikPlayer::MusikPlayerQt::positionChanged, this, &Management::SoundppManagement::positionChanged);
}

QList<Model::Song> SoundppManagement::get_all_songs(){
   return dm->get_all_songs();
}



QList<Model::Song> SoundppManagement::filtered_songs_by_artist(QString artist){
    return dm->filtered_songs_by_artist(artist);
}


Model::Song SoundppManagement::droppedFile(QString filePath)
{
    Model::Song song_to_add = mdr->getMetaDataFromFilePath(filePath);
    dbc->insertSong(song_to_add);
    dm->insertSong(song_to_add);
    return song_to_add; // goes back to ui, for songs model
}

void SoundppManagement::incrementPlayCount(QString songPath)
{
    if(!mpqt->playedOnce()){
//        QString songPath = mpqt->songPath().toString();  // TODO::
        dbc->incrementPlayCount(songPath);
    }
}

bool SoundppManagement::deleteSong(QString filePath)
{

    bool deleted = dbc->deleteSong(filePath);
    if(deleted){
        dm->deleteSong(filePath);
    }
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
