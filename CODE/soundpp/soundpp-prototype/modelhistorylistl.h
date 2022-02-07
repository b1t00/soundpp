#ifndef HISTORYLISTMODEL_H
#define HISTORYLISTMODEL_H

#include "modelsong.h"

#include <QAbstractTableModel>

namespace Model {

class HistoryListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit HistoryListModel(QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void addSong(Model::Song song);
    void removeLastSong();
    bool incrementIndex();
    void resetHistoryIndex();
    Model::Song songByIndex();

    unsigned int indexHistory() const;
    void setIndexHistory(unsigned int indexHistory);

private:
    QList<Model::Song> m_hList;
    int m_indexHistory;
    bool is_playing;
};
}

#endif // HISTORYLISTMODEL_H
