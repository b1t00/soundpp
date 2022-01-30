#include "modeldatamanagement.h"

#include <QDebug>
#include <QStringList>
#include <QDebug>

namespace Model {

QSqlQueryModel *DataManagement::getAllSongs() const
{
    return m_allSongs;
}

void DataManagement::setAllSongs(QSqlQueryModel *allSongs)
{
    m_allSongs = allSongs;
}

DataManagement::DataManagement(QObject *parent)
{

}

DataManagement::DataManagement(QSqlQueryModel  *allSongs,QObject *parent) : QObject(parent),m_allSongs(allSongs)
{

}

QStringList* DataManagement::getAllInterprets()  // TODO::
{
    QStringList *artists = new QStringList;
    for(int i = 0; i < m_allSongs->rowCount(); i++){
          artists->push_back(m_allSongs->record(i).value("artistName").toString());
        }
    return artists;

    }

QList<Artist> DataManagement::create_and_get_artists(){

    QList<Artist> artists;

    for(int i = 0; i < m_allSongs->rowCount(); i++){
        Artist artist;
        artist.setName(m_allSongs->record(i).value("artistName").toString());
        artists.append(artist);
        qInfo() << artist.getName();


    }
    qInfo() << artists.length();
    return artists;

  }


QList<Song> DataManagement::create_and_get_songs(){

    QList<Song> songs;

    for(int i = 0; i < m_allSongs->rowCount(); i++){
        Song song;
        song.setTitle(m_allSongs->record(i).value("songName").toString());
        song.setSongPath(m_allSongs->record(i).value("songPath").toString());
        songs.append(song);
        qInfo() << song.getTitle();


    }
    qInfo() << songs.length();
    return songs;

  }

}





