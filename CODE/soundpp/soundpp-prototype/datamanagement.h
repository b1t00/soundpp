#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H

#include <QObject>
#include <QSqlQueryModel>
#include <QSqlRecord>

namespace Model {

class DataManagement : public QObject
{
    Q_OBJECT
private:
    QSqlQueryModel  *m_allSongs;
public:
    explicit DataManagement(QObject *parent = nullptr);
    explicit DataManagement(QSqlQueryModel  *allSongs, QObject *parent = nullptr);
    void getAllInterprets(QString interpret);
    QSqlQueryModel *getAllSongs() const;
    void setAllSongs(QSqlQueryModel *allSongs);

signals:

};

}
#endif // DATAMANAGEMENT_H
