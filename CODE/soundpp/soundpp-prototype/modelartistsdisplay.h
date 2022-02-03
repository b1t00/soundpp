#ifndef MODELARTISTSDISPLAY_H
#define MODELARTISTSDISPLAY_H

#include <QAbstractTableModel>
#include "modelsong.h"

class display_artist_model : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit display_artist_model(QList<QString> allArtistss, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void removeArtist(QString artist);
    bool containsArtist(QString artist);

private:
    QList<QString> m_allArtists;
};

#endif // MODELARTISTSDISPLAY_H
