#ifndef SOUNDPP_H
#define SOUNDPP_H

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include "databaseconnection.h"

class Soundpp
{
public:
    Soundpp();
    QSqlQueryModel* getQueryModel_all();

private:
    DataBaseConnection *dbconnection;
};

#endif // SOUNDPP_H
