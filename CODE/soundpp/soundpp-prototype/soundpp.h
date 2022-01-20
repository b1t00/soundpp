#ifndef SOUNDPP_H
#define SOUNDPP_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include "databaseconnection.h"

namespace spp {
//class Soundpp;

class Soundpp
{
public:
    Soundpp();
    QSqlQueryModel* getQueryModel_all();
    void insertQuery(QString queryString);

private:
    dbc::DataBaseConnection *dbconnection;
};
}

#endif // SOUNDPP_H
