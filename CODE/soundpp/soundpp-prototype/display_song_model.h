#ifndef DISPLAY_SONG_MODEL_H
#define DISPLAY_SONG_MODEL_H

#include <QAbstractTableModel>
#include <QDateTime>
#include "modelsong.h"

class display_song_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit display_song_model(QList<Model::Song> songs, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    void removeSong(Model::Song song);
    void updateItem(int row, Model::Song song);
    void addSong(Model::Song song);

private:
    QList<Model::Song> m_songs;
};

#endif // DISPLAY_SONG_MODEL_H
