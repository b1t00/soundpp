#ifndef QUEUELISTMODEL_H
#define QUEUELISTMODEL_H

#include "modelsong.h"

#include <QAbstractTableModel>

namespace Model {


class QueueListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit QueueListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setToHistory();
    void appendSong(Model::Song song);

    void playSong(Model::Song triggered_song);
    Model::Song getNextSong();

private:

    QList<Model::Song> m_qSongs;
    QList<Model::Song> m_history;
    bool showHistory;
    int m_index;
};
}

#endif // QUEUELISTMODEL_H
