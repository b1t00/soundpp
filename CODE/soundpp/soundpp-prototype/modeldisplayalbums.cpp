#include "modeldisplayalbums.h"

namespace Model {

DisplayAlbumsModel::DisplayAlbumsModel(QList<QString> allAlbums, QObject *parent)
    : QAbstractTableModel(parent), m_allAlbums(allAlbums)
{
}

QVariant DisplayAlbumsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Albums";
            }
        }
    }

    return QVariant();
}

int DisplayAlbumsModel::rowCount(const QModelIndex &parent) const
{
    return m_allAlbums.size();

}

int DisplayAlbumsModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant DisplayAlbumsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        const QString album = m_allAlbums.at(index.row());
            switch(index.column()){
            case 0: return album;
            }
    }

    return QVariant();
}
}
