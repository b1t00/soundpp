#ifndef MODELDISPLAYARTISTS_H
#define MODELDISPLAYARTISTS_H

#include <QAbstractTableModel>
#include "modelsong.h"

// the Album and Artist Models are very simular, but maybe they will differ in the future
// Question: maybe inheritance of a superclass would be a better solution for the redundance

namespace Model {

class DisplayArtistsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DisplayArtistsModel(QList<QString> allArtistss, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    void removeArtist(QString artist);
    bool containsArtist(QString artist);

    void reset();
    void resetData(QList<QString> changedArtists);

private:
    QList<QString> m_allArtists;
};

}
#endif // MODELDISPLAYARTISTS_H
