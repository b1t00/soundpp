#include "display_song_model.h"

#include <QDebug>

display_song_model::display_song_model(QList<Model::Song> songs,QObject *parent)
    : QAbstractTableModel(parent), m_songs(songs)
{
}

QVariant display_song_model::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Title";
            case 1: return "Song Path";
            case 2: return "Artist";
            case 3: return "Creation Date";
            case 4: return "Playcount";
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
  return 5;
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
            case 2: return song.getArtistName();
            case 3: {
                qint64 epocheTime = song.getAddedTime().toLongLong();
                QDateTime displayTime = QDateTime::fromMSecsSinceEpoch( epocheTime );
//            return displayTime.toString("MM dd yyyy");
            return displayTime.toString("MMM dd yyyy");
            }
            case 4: return song.getPlayCount();
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

bool display_song_model::removeRows(int row, int count, const QModelIndex &parent)
{
    if(row >= rowCount() || row+count-1 >= rowCount()){
        return false;
    }

    beginRemoveRows(parent, row, row+count-1);

    for(int i = 0; i < count; i++){
        m_songs.removeAt(row);
    }

    endRemoveRows();

    return true;

}

void display_song_model::removeSong(Model::Song song)
{

}

void display_song_model::updateItem(int row, Model::Song song)
{
    (m_songs)[row] = song;

    emit dataChanged(createIndex(row, 0),createIndex(row, columnCount()-1));
}
