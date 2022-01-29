#ifndef DISPLAY_ARTISTS_H
#define DISPLAY_ARTISTS_H

#include <QAbstractItemModel>
#include <QStringList>
#include <QString>
#include "artist.h"

class display_artists : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit display_artists(QList<Artist> artists, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    QList<Artist> m_artists;
};

#endif // DISPLAY_ARTISTS_H
