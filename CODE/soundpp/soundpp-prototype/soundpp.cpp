#include "soundpp.h"

Soundpp::Soundpp()
{
    this->dbconnection = new DataBaseConnection();
}

QSqlQueryModel* Soundpp::getQueryModel_all()
{
    return this->dbconnection->getQueryModel_all();
}

