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
    explicit DisplaySongModel(QList<Model::Song> songs, Model::Song *current_playing_song, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

//    void removeSong(Model::Song song);
    void updateSong(int row, Model::Song song);
    void updateSong(Model::Song song);
    void emitSongDataChanged(Model::Song song);
    void addSong(Model::Song song);
    void clear();

    void resetData(QList<Song> otherSongs);
    void reset();

    Model::Song songAt(int index) const;

    QList<Model::Song> songs() const;
    void setSongs(const QList<Model::Song> &songs);

    int m_current_playing_song_index;
signals:
    void indexChanged(int index);
private:
    QList<Model::Song> m_songs;
    Model::Song *m_current_playing_song = nullptr;

};

}
#endif // MODELDISPLAYSONGS_H
