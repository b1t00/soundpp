#ifndef HISTORYLISTMODEL_H
#define HISTORYLISTMODEL_H

#include "modelsong.h"

#include <QAbstractTableModel>

namespace Model {

class HistoryListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit HistoryListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addSong(Model::Song song);

private:
    QList<Model::Song> m_hList;
};
}

#endif // HISTORYLISTMODEL_H
