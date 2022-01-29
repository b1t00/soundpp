#include "display_artists.h"
#include <QDebug>

display_artists::display_artists(QList<Artist> artists, QObject *parent)
    : QAbstractItemModel(parent), m_artists(artists)
{


}

QVariant display_artists::headerData(int section, Qt::Orientation orientation, int role) const
{


    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Artist";
            }


          }
        return QString::number(section +1);
        }
    return QVariant();
}

QModelIndex display_artists::index(int row, int column, const QModelIndex &parent) const
{
    return QModelIndex();
}

QModelIndex display_artists::parent(const QModelIndex &index) const
{
    return QModelIndex();
}

int display_artists::rowCount(const QModelIndex &parent) const
{

    return m_artists.size();
}

int display_artists::columnCount(const QModelIndex &parent) const
{

    return 1;
}

QVariant display_artists::data(const QModelIndex &index, int role) const
{

    if(index.isValid())
        return QVariant();


    if(role == Qt::DisplayRole ) {
        const Artist artist =  m_artists.at(index.row());


        switch(index.column()){
          case 0: return artist.getName();
        }

//        for(int i = 0; i < m_artists->size(); i ++){
//            if(i == artist){
//                return artist;
//            }

//        }


     }
    return QVariant();
}
