#include "displayplaylistmodel.h"
namespace Model {

DisplayPlaylistModel::DisplayPlaylistModel(QList<Song> songs, QObject *parent)
    : QAbstractTableModel(parent), m_all_songs(songs)
{
}

QVariant DisplayPlaylistModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Playlist";
            }
        }
    }
    return QVariant();
}

int DisplayPlaylistModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int DisplayPlaylistModel::columnCount(const QModelIndex &parent) const
{
        return 1;
}

QVariant DisplayPlaylistModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
}
