#include "modelhistorylistl.h"
#include <QBrush>
#include <QColor>
#include <QDebug>

namespace Model {
HistoryListModel::HistoryListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_indexHistory = -1;
}

QVariant HistoryListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(role == Qt::DisplayRole){
        if(orientation == Qt::Horizontal){
            switch(section){
            case 0: return "Artist";
            case 1: return "Title";
            }
        }
    }
    return QVariant();

}

int HistoryListModel::rowCount([[maybe_unused]]const QModelIndex &parent) const
{
    return m_hSongs.size();
}

int HistoryListModel::columnCount([[maybe_unused]]const QModelIndex &parent) const
{
    return 2;
}

//QVariant HistoryListModel::data(const QModelIndex &index, int role) const
//{
//    if (!index.isValid())
//        return QVariant();

//    if(role == Qt::DisplayRole){
//        const Model::Song s = m_hSongs.at(index.row());
//            switch(index.column()){
//            case 0: return s.getArtistName();
//            case 1: return s.getTitle();
//            }
//    }
//    return QVariant();
//}

QVariant HistoryListModel::data(const QModelIndex &index, int role) const
 {
     if ( !index.isValid() )
         return QVariant();

     switch ( role )
     {

        case Qt::BackgroundRole:
        {
            if(index.row()==(m_indexHistory+1)){
//               return QVariant(QBrush (QColor(Qt::green)));
               return QVariant(QBrush (QColor(102,255,178)));
            }
            break;
        }

        case Qt::DisplayRole:
        {
            const Model::Song s = m_hSongs.at(index.row());
            switch(index.column()){
                case 0: return s.getArtistName();
                case 1: return s.getTitle();
            }

        }

//        case Qt::TextAlignmentRole:
//        {

//           if (1==col)
//              return QVariant ( Qt::AlignVCenter | Qt::AlignLeft );

//           if (2==col)
//              return QVariant ( Qt::AlignVCenter | Qt::AlignTrailing );

//           return QVariant ( Qt::AlignVCenter | Qt::AlignHCenter );

//        }
     }
     return QVariant();

  }



void HistoryListModel::addSong(Model::Song song)
{
    beginInsertRows(QModelIndex(),0,0);
    m_hSongs.insert(0,song);
    endInsertRows();
}

void HistoryListModel::removeLastSong()
{
    beginRemoveRows(QModelIndex(),0,0);
    m_hSongs.pop_front();
    endRemoveRows();
}

bool HistoryListModel::incrementIndex()
{
    if(m_indexHistory < m_hSongs.size()-2){
        m_indexHistory++;
        return true;
    }
    return false;
}

void HistoryListModel::resetHistoryIndex()
{
    m_indexHistory = -1;
}

Song HistoryListModel::songByIndex()
{
    if(m_indexHistory < m_hSongs.size()){
        return m_hSongs.at(m_indexHistory);
    }
}

unsigned int HistoryListModel::indexHistory() const
{
    return m_indexHistory;
}

void HistoryListModel::setIndexHistory(unsigned int indexHistory)
{
    m_indexHistory = indexHistory;
}

QList<Model::Song> HistoryListModel::hSongs() const
{
    return m_hSongs;
}

void HistoryListModel::setHSongs(const QList<Model::Song> &hSongs)
{
    m_hSongs = hSongs;
}
}
