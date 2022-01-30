#include "display_song_model.h"

display_song_model::display_song_model(QList<Model::Song> songs,QObject *parent)
    : QAbstractTableModel(parent), m_songs(songs)
{
}

QVariant display_song_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Songs"; 
//            case 1: return "path";
            }

        }
    }

    return QVariant();
}

int display_song_model::rowCount(const QModelIndex &parent) const
{
   return m_songs.size();
}

int display_song_model::columnCount(const QModelIndex &parent) const
{
  return 2;
}

QVariant display_song_model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        const Model::Song song = m_songs.at(index.row());
            switch(index.column()){
            case 0: return song.getTitle();
            case 1: return song.getSongPath();
            }

    }
    return QVariant();
}

QString display_song_model::getSongPath(const QModelIndex &parent)
{
    const Model::Song song = m_songs.at(parent.row());
    switch(parent.column()){
    case 0: return song.getTitle();
    case 1:return song.getSongPath();
    }
}
