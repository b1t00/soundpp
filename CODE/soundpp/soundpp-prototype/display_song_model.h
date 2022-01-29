#ifndef DISPLAY_SONG_MODEL_H
#define DISPLAY_SONG_MODEL_H

#include <QAbstractTableModel>
#include "song.h"

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

private:
    QList<Model::Song> m_songs;
};

#endif // DISPLAY_SONG_MODEL_H
