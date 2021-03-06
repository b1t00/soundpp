#include "modeldisplayartists.h"

namespace Model {

DisplayArtistsModel::DisplayArtistsModel(QList<QString> allArtists,QObject *parent)
    : QAbstractTableModel(parent), m_allArtists(allArtists)
{
}

QVariant DisplayArtistsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Artist";
            }
        }
    }

    return QVariant();
}

int DisplayArtistsModel::rowCount(const QModelIndex &parent) const
{

    return m_allArtists.size();
}

int DisplayArtistsModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant DisplayArtistsModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        const QString artist = m_allArtists.at(index.row());
            switch(index.column()){
            case 0: return artist;
            }

    }
    return QVariant();
}

void DisplayArtistsModel::sort(int column, Qt::SortOrder order)
{
    switch (column) {
    case 0: {
        order == Qt::AscendingOrder ?
                    std::sort(m_allArtists.rbegin(),m_allArtists.rend()):
                    std::sort(m_allArtists.begin(),m_allArtists.end())  ;
        reset();
        break;
    }
    }
}

void DisplayArtistsModel::removeArtist(QString artist_to_remove)
{
    for(int i = 0; i < m_allArtists.size(); i++){
        if(m_allArtists.at(i) == artist_to_remove) {
            m_allArtists.removeAt(i);
            removeRow(i);
        }
    }
}

bool DisplayArtistsModel::containsArtist(QString artist)
{
    return (m_allArtists.contains(artist)) ? true : false;
}

void DisplayArtistsModel::reset()
{
    beginResetModel();
    endResetModel();
}

void DisplayArtistsModel::resetData(QList<QString> changedArtists)
// refresh all artists, because maybe names disapeard or changed
{
    beginResetModel();
    m_allArtists = changedArtists;
    endResetModel();
}

}
