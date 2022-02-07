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

    void playNext(Model::Song song_selected);
    void playNext(QList<Model::Song> songs_selection);
    void appendSong(Model::Song song);
    void appendSongs(QList<Model::Song> songs);
    void removeSongs(QList<int> indeces);

    bool hasSongs();
    Model::Song nextSong();


    QList<Model::Song> qSongs() const;
    void setQSongs(const QList<Model::Song> &qSongs);

private:

    QList<Model::Song> m_qSongs;

};
}

#endif // QUEUELISTMODEL_H
