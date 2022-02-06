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
}
