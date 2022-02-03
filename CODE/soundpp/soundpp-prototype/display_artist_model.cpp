#include "display_artist_model.h"

display_artist_model::display_artist_model(QList<QString> allArtists,QObject *parent)
    : QAbstractTableModel(parent), m_allArtists(allArtists)
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

    return m_allArtists.size();
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
        const QString artist = m_allArtists.at(index.row());
            switch(index.column()){
            case 0: return artist;
            }

    }

    // FIXME: Implement me!
    return QVariant();
}

void display_artist_model::removeArtist(QString artist_to_remove)
{
    for(int i = 0; i < m_allArtists.size(); i++){
        if(m_allArtists.at(i) == artist_to_remove) {
            m_allArtists.removeAt(i);
            removeRow(i);
        }
    }
}

bool display_artist_model::containsArtist(QString artist)
{
    return (m_allArtists.contains(artist)) ? true : false;
}
