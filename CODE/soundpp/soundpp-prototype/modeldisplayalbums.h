#ifndef MODELDISPLAYALBUMS_H
#define MODELDISPLAYALBUMS_H

#include <QAbstractTableModel>

namespace Model {


class DisplayAlbumsModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit DisplayAlbumsModel(QList<QString> allAlbums, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    void removeAlbum(QString album);
    bool containsAlbum(QString album);

    void reset();

private:
    QList<QString> m_allAlbums;
};
}

#endif // MODELDISPLAYALBUMS_H
