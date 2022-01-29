#include "display_artist_model.h"

display_artist_model::display_artist_model(QList<Model::Artist> artists,QObject *parent)
    : QAbstractTableModel(parent), m_artists(artists)
{
}

QVariant display_artist_model::headerData(int section, Qt::Orientation orientation, int role) const
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

int display_artist_model::rowCount(const QModelIndex &parent) const
{

    return m_artists.size();
}

int display_artist_model::columnCount(const QModelIndex &parent) const
{

    return 1;
}

QVariant display_artist_model::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        const Model::Artist artist = m_artists.at(index.row());
            switch(index.column()){
            case 0: return artist.getName();
            }

    }

    // FIXME: Implement me!
    return QVariant();
}
