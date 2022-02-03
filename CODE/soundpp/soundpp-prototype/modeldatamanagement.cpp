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

DataManagement::DataManagement(QList<Model::Song> *all_songs, QObject *parent) :
    QObject(parent), m_all_songs(all_songs)
{
}

QList<Model::Song> DataManagement::get_all_songs() const
{
    QList<Model::Song> all_songs_copy = *m_all_songs;
    return all_songs_copy;
}

void DataManagement::setAllSongs(QList<Model::Song> *all_songs)
{
    m_all_songs = all_songs;
}



QList<Model::Song> DataManagement::filtered_songs_by_artist(QString artist){

    QList<Model::Song> filtered_songs;

    for(int i = 0; i < m_all_songs->size(); i++){
     if(m_all_songs->at(i).getArtistName() == artist){
            filtered_songs.append(m_all_songs->at(i));
        }
    }
    return filtered_songs;
}




QList<Model::Song> DataManagement::search_result(QString search){

    QList<Model::Song> search_result;

    for(int i = 0; i < m_all_songs->size(); i ++){
        if(m_all_songs->at(i).getArtistName().toUpper().contains(search.toUpper())
        || m_all_songs->at(i).getTitle().toUpper().contains(search.toUpper())
        || m_all_songs->at(i).getAlbumName().toUpper().contains(search.toUpper())){

            search_result.append(m_all_songs->at(i));


            }



        }
    return search_result;
}




//    for(int i =0; i< m_all_songs.size(); ++i) {
////        for(int j = 0; j < m_all_songs.at(i).getArtistName().size(); ++j){

//             compare  = m_all_songs.at(i).getArtistName().at(search.length() - 1);

//             deineMudda[i].append(compare);



//             if(compare.toUpper() == search.toUpper()){
//                 search_result.append(m_all_songs.at(i));
//              }



//           }

////            if(m_all_songs.at(i).getArtistName() == search )  {
////                search_result.append(m_all_songs.at(i));




QList<QString> DataManagement::allArtists()
{
    QList<QString> allArtists;
    for(Model::Song s : *m_all_songs){
        if(!allArtists.contains(s.getArtistName())){
            allArtists.append(s.getArtistName());
        };
    }
    std::sort(allArtists.begin(), allArtists.end());
    return allArtists;
}

bool DataManagement::deleteSong(QString filePath)
{
    for(int i = 0; i < m_all_songs->size(); i++){
        if(m_all_songs->at(i).getSongPath() == filePath){
//            qDebug() <<  m_all_songs->at(i).getAlbumName() << " wird removed";
            m_all_songs->removeAt(i);
            return true;
        }
    }
    return false;
}

bool DataManagement::insertSong(Song song_to_add)
{
    m_all_songs->append(song_to_add);
    return true;
}




}





