#include "modeldisplaysongs.h"

#include <QDebug>
#include <qbrush.h>
#include <qcolor.h>

namespace Model {

DisplaySongModel::DisplaySongModel(QList<Model::Song> songs,QObject *parent)
    : QAbstractTableModel(parent), m_songs(songs)
{
    std::sort(m_songs.begin(),m_songs.end(),compareByAlbumName);
}

DisplaySongModel::DisplaySongModel(QList<Song> songs, Song *current_playing_song, QObject *parent)
    : QAbstractTableModel(parent),m_songs(songs), m_current_playing_song(current_playing_song)
{

}

QVariant DisplaySongModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Song path";
            case 1: return "Song title";
            case 2: return "Artist";
            case 3: return "Album";
            case 4: return "nr";
            case 5: return "Label";
            case 6: return "Katalog Nr";
            case 7: return "Creation date";
            case 8: return "Playcount";
            }

        }
    }

    return QVariant();
}

int DisplaySongModel::rowCount(const QModelIndex &parent) const
{
   return m_songs.size();
}

int DisplaySongModel::columnCount(const QModelIndex &parent) const
{
  return 9;
}

QVariant DisplaySongModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    switch ( role )
    {
       case Qt::BackgroundRole:
       {
//        if(m_current_playing_song != nullptr){
           if(m_songs.at(index.row()) == m_current_playing_song){
//               m_current_playing_song_index = index.row();
//              return QVariant(QBrush (QColor(204,255,229)));
              return QVariant(QBrush (QColor(102,255,178)));
           }
           // otherwise background is white
//       }
//        return QVariant(QBrush (QColor(Qt::white)));
    }


    case  Qt::DisplayRole:
    {
        const Model::Song song = m_songs.at(index.row());
            switch(index.column()){
            case 0: return song.getSongPath();
            case 1: return song.getTitle();
            case 2: return song.getArtistName();
            case 3: return song.getAlbumName();
            case 4: return song.getAlbumNr();
            case 5: return song.getLabelName();
            case 6: return song.getLabelNr();
            case 7: {
                    qint64 epocheTime = song.getAddedTime().toLongLong();
                    QDateTime displayTime = QDateTime::fromMSecsSinceEpoch( epocheTime );
        //            return displayTime.toString("MM dd yyyy");
                    return displayTime.toString("MMM dd yyyy");
            }
            case 8: return song.getPlayCount();
        }
    }
    }
    return QVariant();
}


bool DisplaySongModel::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row >= rowCount() || row+count-1 >= rowCount()) return false;

    beginRemoveRows(parent, row, row+count-1);

    for(int i = 0; i < count; i++) m_songs.removeAt(row);

    endRemoveRows();

    return true;
}

void DisplaySongModel::sort(int column, Qt::SortOrder order)
{
    switch (column) {
    case 0: {
        // path comparison is maybe an interesting topic
        break;
    }
    case 1: {
        order == Qt::AscendingOrder ?
                    std::sort(m_songs.begin(),m_songs.end(),compareBySongTitle)  :
                    std::sort(m_songs.rbegin(),m_songs.rend(),compareBySongTitle);
        reset();
        break;
    }
    case 2: {
        order == Qt::AscendingOrder ?
                    std::sort(m_songs.begin(),m_songs.end(),compareByArtistName)  :
                    std::sort(m_songs.rbegin(),m_songs.rend(),compareByArtistName);
        reset();
        break;
    }
    case 3: {
        order == Qt::AscendingOrder ?
                    std::sort(m_songs.begin(),m_songs.end(),compareByAlbumName)  :
                    std::sort(m_songs.rbegin(),m_songs.rend(),compareByAlbumName);
        reset();
        break;
    }
    case 4: {
        order == Qt::AscendingOrder ?
                    std::sort(m_songs.begin(),m_songs.end(),compareByAlbumNr)  :
                    std::sort(m_songs.rbegin(),m_songs.rend(),compareByAlbumNr);
        reset();
        break;
    }
    case 8: {
        order == Qt::AscendingOrder ?
                    std::sort(m_songs.begin(),m_songs.end(),compareByPlayCount)  :
                    std::sort(m_songs.rbegin(),m_songs.rend(),compareByPlayCount);
        reset();
        break;
    }
    }
}

void DisplaySongModel::removeSong(Model::Song song)
{
}

void DisplaySongModel::updateSong(int row, Model::Song song)
{
    (m_songs)[row] = song;

    emit dataChanged(createIndex(row, 0),createIndex(row, columnCount()-1));
}

void DisplaySongModel::updateSong(Song song)
{
    if(m_songs.size() > 1){
        for(int i = 0; i < m_songs.size() ; i++){
            if(m_songs.at(i).getSongPath() == song.getSongPath()){
                emit dataChanged(createIndex(i, 0),createIndex(i, columnCount()-1));
                break;
            }
        }
    }
}


void DisplaySongModel::addSong(Model::Song song)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_songs.append(song);
    endInsertRows();
//    (m_songs)[0] = song;
//    qDebug() << "add song " << song.getAlbumName();
//    emit dataChanged(createIndex(m_songs.size()-1, 0),createIndex(m_songs.size()-1, columnCount()-1));

}

void DisplaySongModel::clear()
{
    beginResetModel();
    m_songs.clear();
    endResetModel();
}

void DisplaySongModel::resetData(QList<Song> otherSongs)
{
    beginResetModel();
    m_songs = otherSongs;
    endResetModel();
}

void DisplaySongModel::reset()
{
    beginResetModel();
    endResetModel();
//    qDebug() << "last index" << m_current_playing_song_index;
//    m_current_playing_song_index =m_songs.count(*m_current_playing_song);
//    qDebug() << "now index " << m_current_playing_song_index;
}

Song DisplaySongModel::songAt(int index) const
{
    return m_songs.at(index);
}

QList<Model::Song> DisplaySongModel::songs() const
{
    return m_songs;
}

void DisplaySongModel::setSongs(const QList<Model::Song> &songs)
{
    m_songs = songs;
}
}
