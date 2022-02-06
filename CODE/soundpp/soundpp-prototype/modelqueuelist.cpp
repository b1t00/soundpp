#include "modelqueuelist.h"
namespace Model {

QueueListModel::QueueListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    m_index = -99;
}

QVariant QueueListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
//    if(role == Qt::DisplayRole){
//        if(orientation == Qt::Horizontal){
//            switch(section){
//            case 0: return "Queue List";
//            }
//        }
//    }
    return QVariant();
}

int QueueListModel::rowCount(const QModelIndex &parent) const
{
    return m_qSongs.size();
}

int QueueListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant QueueListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        const Model::Song s = m_qSongs.at(index.row());
            switch(index.column()){
            case 0: return s.getTitle();
            }
    }
    return QVariant();
}

void QueueListModel::setToHistory()
{
    showHistory = true;
    beginResetModel();
    m_qSongs.clear();
    endResetModel();
}

void QueueListModel::appendSong(Song song)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_qSongs.append(song);
    endInsertRows();
}

void QueueListModel::playSong(Song triggered_song)
{
    beginInsertRows(QModelIndex(),0,0);
    m_qSongs.insert(0, triggered_song);
    endInsertRows();
}

Song QueueListModel::getNextSong()
{
//    m_index++;
//    m_index++;
//    m_history.append(m_qSongs.at(0));
    m_qSongs.removeAt(0);
    beginRemoveRows(QModelIndex(), 0, 0);
    endRemoveRows();
    return m_qSongs.at(0);
}
}
