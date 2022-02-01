#include "modeldatamanagement.h"

#include <QDebug>
#include <QStringList>
#include <QDebug>
#include <QSet>

//#include <QSort>

namespace Model {

DataManagement::DataManagement(QObject *parent)
{

}

DataManagement::DataManagement(QList<Model::Song> all_songs, QObject *parent) :
    QObject(parent), m_all_songs(all_songs)
{


}

QList<Model::Song> DataManagement::get_all_songs() const
{
    return m_all_songs;
}

void DataManagement::setAllSongs(QList<Model::Song> all_songs)
{
    m_all_songs = all_songs;
}



QList<Model::Song> DataManagement::filtered_songs_by_artist(QString artist){


    QList<Model::Song> filtered_songs;


    for(int i = 0; i < m_all_songs.size(); i++){
     if(m_all_songs.at(i).getArtistName() == artist){
            filtered_songs.append(m_all_songs.at(i));
        }
    }
    qInfo() << filtered_songs.size();
    return filtered_songs;
}

bool DataManagement::deleteSong(QString filePath)
{
    for(int i = 0; i < m_all_songs.size(); i++){
        if(m_all_songs.at(i).getSongPath() == filePath){
            qDebug() <<  m_all_songs.at(i).getAlbumName() << " wird removed";
            m_all_songs.removeAt(i);
            return true;
        }
    }
    return false;
}

bool DataManagement::insertSong(Song song_to_add)
{
    m_all_songs.append(song_to_add);
    return true;
}


}





