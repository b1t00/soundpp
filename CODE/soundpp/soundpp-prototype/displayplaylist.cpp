#include "displayplaylist.h"

namespace Model {



DisplayPlaylist::DisplayPlaylist(QObject *parent)
    : QAbstractTableModel(parent)
{
}

QVariant DisplayPlaylist::headerData(int section, Qt::Orientation orientation, int role) const
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

int DisplayPlaylist::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int DisplayPlaylist::columnCount(const QModelIndex &parent) const
{
        return 1;
}

QVariant DisplayPlaylist::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
}
