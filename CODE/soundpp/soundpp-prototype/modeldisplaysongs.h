#ifndef MODELDISPLAYSONGS_H
#define MODELDISPLAYSONGS_H

#include <QAbstractTableModel>
#include <QDateTime>
#include "modelsong.h"

namespace Model {

class DisplaySongModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DisplaySongModel(QList<Model::Song> songs, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void removeSong(Model::Song song);
    void updateSong(int row, Model::Song song);
    void addSong(Model::Song song);
    void clear();

private:
    QList<Model::Song> m_songs;
};

}
#endif // MODELDISPLAYSONGS_H
