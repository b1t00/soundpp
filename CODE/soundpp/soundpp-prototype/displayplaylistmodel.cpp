#include "displayplaylistmodel.h"
namespace Model {

DisplayPlaylistModel::DisplayPlaylistModel(QList<Playlist> playlists, QObject *parent)
    : QAbstractTableModel(parent), m_all_playlists(playlists)
{
}

QVariant DisplayPlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Playlists";
            case 1: return "Playlist_ID";
            }
        }
    }
    return QVariant();
}

int DisplayPlaylistModel::rowCount(const QModelIndex &parent) const
{
    return m_all_playlists.size();
}

int DisplayPlaylistModel::columnCount(const QModelIndex &parent) const
{
        return 2;
}

QVariant DisplayPlaylistModel::data(const QModelIndex &index, int role) const
{

    if (!index.isValid())
        return QVariant();

   if(role == Qt::DisplayRole){
       const Model::Playlist playlist = m_all_playlists.at(index.row());

       switch(index.column()){
       case 0 : return playlist.getPlaylistName();
       case 1 : return playlist.getPlaylistID();
       }
   }
   return QVariant();
}

void DisplayPlaylistModel::addPlaylist(Model::Playlist playlist){
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_all_playlists.append(playlist);
    endInsertRows();

}

bool DisplayPlaylistModel::removeRows(int row, int count, const QModelIndex &parent ){
    if(row >= rowCount() || row+count-1 >= rowCount()) return false;
    beginRemoveRows(parent, row, row+count-1);
    for(int i=0; i < count; i++) m_all_playlists.removeAt(row);

    endRemoveRows();

    return true;

}
}
