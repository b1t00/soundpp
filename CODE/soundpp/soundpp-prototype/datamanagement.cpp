#include "datamanagement.h"

#include <QDebug>

namespace Model {

QSqlQueryModel *DataManagement::getAllSongs() const
{
    return m_allSongs;
}

void DataManagement::setAllSongs(QSqlQueryModel *allSongs)
{
    m_allSongs = allSongs;
}

DataManagement::DataManagement(QObject *parent)
{

}

DataManagement::DataManagement(QSqlQueryModel  *allSongs,QObject *parent) : QObject(parent),m_allSongs(allSongs)
{

}

void DataManagement::getAllInterprets(QString interpret) // TODO::
{
    for(int i = 0; i < m_allSongs->rowCount(); i++){
        if(m_allSongs->record(i).value("artistName") == interpret){
            qDebug() << m_allSongs->record(i).value("songName").toString();
        }
    }
}
}
