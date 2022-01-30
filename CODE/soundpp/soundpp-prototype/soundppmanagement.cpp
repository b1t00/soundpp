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

void SoundppManagement::deleteSong(QString filePath)
{
    dbc->deleteSong(filePath);
}

bool SoundppManagement::pressPlay()
{
    incrementPlayCount();
    return mpqt->pressPlay();
}

void SoundppManagement::doubleclickPlay(QString songPath)
{
    mpqt->setSongPath(songPath);
    pressPlay();
}


void SoundppManagement::setVolume(int volume)
{
    mpqt->setVolume(volume);
}

void SoundppManagement::setPosition(int position)
{
    mpqt->setPosition(position);

}

void SoundppManagement::on_songs_tableView_doubleClicked(const QModelIndex &index)
{

}

}
