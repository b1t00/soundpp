#include "soundppmanagement.h"

#include <QUrl>

namespace Management {

SoundppManagement::SoundppManagement(QObject *parent) : QObject(parent)
{
    dbc = new Database::DataBaseConnection();
    mpqt = new MusikPlayer::MusikPlayerQt();
    mdr = new MetaData::MetaDataFromFile();
    dm = new Model::DataManagement(dbc->get_and_create_all_Songs(), dbc->get_and_create_all_Playlists());


    //musikplayer connection forwarding
    connect(mpqt, &MusikPlayer::MusikPlayerQt::durationChanged, this, &Management::SoundppManagement::durationChanged);
    connect(mpqt, &MusikPlayer::MusikPlayerQt::positionChanged, this, &Management::SoundppManagement::positionChanged);
    connect(mpqt, &QMediaPlayer::mediaStatusChanged, this, &Management::SoundppManagement::playerstatusChanged);
    mpqt->setVolume(75);


}

QList<Model::Song> SoundppManagement::get_all_songs(){
   return dm->get_all_songs();
}

QList<Model::Playlist> SoundppManagement::get_all_playlists(){
    return dm->get_all_playlists();
}

void SoundppManagement::new_playlist(Model::Playlist new_playlist){
     dbc->insertPlaylist(new_playlist);
     dm->insert_playlist(new_playlist);
}

bool SoundppManagement::deletePlaylist(int playlistID){
   bool deleted = dbc->deletePlaylist(playlistID);

   if(deleted) deleted = dm->deletePlaylist(playlistID);
   return deleted;

}

void SoundppManagement::songs_for_paylist(QString playlistName, Model::Song song){
     dm->add_songs_for_playlist(song, playlistName);
}



QList<Model::Song> SoundppManagement::filtered_songs_by_artist(QString artist){
    return dm->filtered_songs_by_artist(artist);
}

QList<Model::Song> SoundppManagement::filtered_songs_by_album(QString album)
{
    return dm->filtered_songs_by_album(album);
}

QList<Model::Song> SoundppManagement::search_result(QString search){
    return dm->search_result(search);
}

QList<QString> SoundppManagement::allArtists()
{
    return dm->allArtists();
}

QList<QString> SoundppManagement::allAlbums()
{
    return dm->allAlbums();
}


Model::Song SoundppManagement::droppedFile(QString filePath)
{
    Model::Song song_to_add = mdr->getMetaDataFromFilePath(filePath);
    dbc->insertSong(song_to_add);
    dm->insertSong(song_to_add);
    return song_to_add; // goes back to ui, for songs model
}

bool SoundppManagement::containsSongPath(QString songPath)
{
    return dm->containsSongPath(songPath);
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
    bool deleted = dbc->deleteSong(filePath); // bool if song removed from db
    if(deleted) deleted = dm->deleteSong(filePath);
    return deleted;
}

Model::Song SoundppManagement::editSong(Model::Song edited_song)
{
    if(dm->editSong(dbc->editSong(edited_song))){
        return dbc->editSong(edited_song);
    }
    qWarning() << "dm konnte song nicht ersetzten";
    return Model::Song();
}

void SoundppManagement::press_mute(bool mute){
    mpqt->setMuted(mute);
}

void SoundppManagement::addToQueue(QUrl url)
{
    mpqt->addToQueue(url);
}

bool SoundppManagement::pressPlay()
{
    if(!mpqt->isAudioAvailable()) return false;
    return mpqt->pressPlay();
}

void SoundppManagement::stopPlaying()
{
    mpqt->stop();
}

void SoundppManagement::playSong(QString songPath)
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

bool SoundppManagement::isPlaying() const
{
    return mpqt->isPlayling();
}

}
