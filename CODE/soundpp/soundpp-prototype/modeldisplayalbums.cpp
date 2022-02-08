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

void DisplayAlbumsModel::sort(int column, Qt::SortOrder order)
{
    switch (column) {
    case 0: {
        order == Qt::AscendingOrder ?
                    std::sort(m_allAlbums.rbegin(),m_allAlbums.rend()):
                    std::sort(m_allAlbums.begin(),m_allAlbums.end())  ;
        reset();
        break;
    }
    }
}

void DisplayAlbumsModel::removeAlbum(QString album_to_remove)
{
    for(int i = 0; i < m_allAlbums.size(); i++){
        if(m_allAlbums.at(i) == album_to_remove) {
            m_allAlbums.removeAt(i);
            removeRow(i);
        }
    }
}

bool DisplayAlbumsModel::containsAlbum(QString album)
{
    return (m_allAlbums.contains(album)) ? true : false;
}

void DisplayAlbumsModel::reset()
{
    beginResetModel();
    endResetModel();
}

void DisplayAlbumsModel::resetData(QList<QString> newAlbums)
// refresh all albums, because maybe names disapeard or changed
{
    beginResetModel();
    m_allAlbums = newAlbums;
    endResetModel();
}
}
