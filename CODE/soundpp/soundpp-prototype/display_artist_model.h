#ifndef DISPLAY_ARTIST_MODEL_H
#define DISPLAY_ARTIST_MODEL_H

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

private:
    QList<QString> m_allArtists;
};

#endif // DISPLAY_ARTIST_MODEL_H
