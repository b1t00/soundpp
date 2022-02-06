#include "modelqueuelist.h"
#include<QDebug>

namespace Model {

QueueListModel::QueueListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant QueueListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Artist";
            case 1: return "Title";
            }
        }
    }
    return QVariant();
}

int QueueListModel::rowCount(const QModelIndex &parent) const
{
    return m_qSongs.size();
}

int QueueListModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant QueueListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        const Model::Song s = m_qSongs.at(index.row());
            switch(index.column()){
            case 0: return s.getArtistName();
            case 1: return s.getTitle();
            }
    }
    return QVariant();
}

void QueueListModel::playNext(Model::Song song_selected)
{
//    qDebug() << "playy next";

    beginInsertRows(QModelIndex(),0,0);
    m_qSongs.insert(0, song_selected);
    endInsertRows();
}

void QueueListModel::playNext(QList<Song> songs_selection)
{

    beginInsertRows(QModelIndex(),0,songs_selection.size()-1);
    for(int i = 0; i < songs_selection.size(); i++){
        m_qSongs.insert(0, songs_selection.at(i));
    }
    endInsertRows();
}

void QueueListModel::appendSong(Song song)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_qSongs.append(song);
    endInsertRows();
}

void QueueListModel::appendSongs(QList<Song> songs)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount() + songs.size()-1);
//    for(Model::S)
    m_qSongs.append(songs);
    endInsertRows();
}

bool QueueListModel::hasSongs()
{
    return m_qSongs.size();
}


Song QueueListModel::nextSong()
{
    Model::Song song_next = m_qSongs.at(0);
    beginRemoveRows(QModelIndex(), 0, 0);
    m_qSongs.removeFirst();
    endRemoveRows();
    return song_next;
}
}
