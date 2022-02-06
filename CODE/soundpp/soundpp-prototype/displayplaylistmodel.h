#ifndef DISPLAYPLAYLISTMODEL_H
#define DISPLAYPLAYLISTMODEL_H

#include <QAbstractTableModel>
#include "modelsong.h"
#include "playlist.h"

namespace Model {

class DisplayPlaylistModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DisplayPlaylistModel(QList<Model::Playlist> playlists, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<Model::Playlist> m_all_playlists;
};
}

#endif // DISPLAYPLAYLISTMODEL_H
