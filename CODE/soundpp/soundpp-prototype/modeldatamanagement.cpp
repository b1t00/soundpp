#include "modeldatamanagement.h"

#include <QDebug>
#include <QStringList>
#include <QDebug>
#include <QSet>

//#include <QSort>

namespace Model {

DataManagement::DataManagement([[maybe_unused]]QObject *parent)
{

}

DataManagement::DataManagement(QList<Model::Song> *all_songs, QList<Model::Playlist> *all_playlists ,QObject *parent) :
    QObject(parent), m_all_songs(all_songs), m_all_playlists(all_playlists)
{
}

QList<Model::Song> DataManagement::get_all_songs() const
{
    QList<Model::Song> all_songs_copy = *m_all_songs;
    return all_songs_copy;
}

QList<Model::Playlist> DataManagement::get_all_playlists()
{
    QList<Model::Playlist> all_playlists_copy = *m_all_playlists;
    return all_playlists_copy;
}

bool DataManagement::insert_playlist(Model::Playlist new_playlist){
    m_all_playlists->append(new_playlist);
    return true;
}

void DataManagement::setAllSongs(QList<Model::Song> *all_songs)
{
    m_all_songs = all_songs;
}

void DataManagement::add_songs_for_playlist(Model::Song song, QString playlistName)
{


    for(int i = 0; i < m_all_playlists->size(); i++){
        if(m_all_playlists->at(i).getPlaylistName() == playlistName){
           Playlist playlist = m_all_playlists->at(i);
           playlist.add_song_to_playlist(song);
//           qInfo() << playlist.getSongs_of_playlist().size();

        }
    }

    for(int i = 0; i < m_all_playlists->size(); i++){
        if(m_all_playlists->at(i).getPlaylistName() == playlistName){
//            qInfo() << m_all_playlists->at(i).getSongs_of_playlist().at(1).getTitle();
        }


}


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

QList<Model::Song> DataManagement::filtered_songs_by_album(QString album)
{
    QList<Model::Song> filtered_songs;

    for(int i = 0; i < m_all_songs->size(); i++){
     if(m_all_songs->at(i).getAlbumName() == album){
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

QList<QString> DataManagement::allAlbums()
{
    QList<QString> allAlbums;

    for(auto s : *m_all_songs){
        if(!allAlbums.contains(s.getAlbumName())){
            allAlbums.append(s.getAlbumName());
        };
    }
    std::sort(allAlbums.begin(), allAlbums.end());
    return allAlbums;

}


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

Song DataManagement::randomSong()
/*
 * Method for autoPlay random song
 * in the future we could use an algorithm to
 * get a good next song
 */
{
    int randomIndex = std::rand() % m_all_songs->size();
    return m_all_songs->at(randomIndex);
}

bool DataManagement::isAnySongAvalaible()
{
    return (m_all_songs->size() > 0 ) ? true : false;
}

bool DataManagement::deletePlaylist(int playlistID){


    for(int i = 0; i < m_all_playlists->size(); i++){
        if(m_all_playlists->at(i).getPlaylistID() == playlistID){
            m_all_playlists->removeAt(i);
            return true;
        }
    }
    return false;
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

bool DataManagement::editSong(Song song_from_db)
{
    for(int i = 0; i < m_all_songs->size(); i++){
        if(m_all_songs->at(i).getSongPath() == song_from_db.getSongPath()){
            m_all_songs->replace(i, song_from_db);
            return true;
        }
    }
    return false;
}

bool DataManagement::containsSongPath(QString songPath)
{
    for(Model::Song s : *m_all_songs){
//        qDebug() << "s path" << s.getSongPath();
//        qDebug() << "2 path" << QString(songPath) << "\n -------------- ";
        if(s.getSongPath() == songPath) return true;
    }
    return false;
}




}





