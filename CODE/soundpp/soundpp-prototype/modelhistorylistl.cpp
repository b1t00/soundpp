#include "modelhistorylistl.h"
namespace Model {
HistoryListModel::HistoryListModel(QObject *parent)
    : QAbstractTableModel(parent)
{
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

int HistoryListModel::rowCount(const QModelIndex &parent) const
{
    return m_hList.size();
}

int HistoryListModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant HistoryListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if(role == Qt::DisplayRole){
        const Model::Song s = m_hList.at(index.row());
            switch(index.column()){
            case 0: return s.getArtistName();
            case 1: return s.getTitle();
            }
    }
    return QVariant();
}

void HistoryListModel::addSong(Model::Song song)
{
    beginInsertRows(QModelIndex(),0,0);
    m_hList.insert(0,song);
    endInsertRows();
}
}