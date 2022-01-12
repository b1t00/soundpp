#include "soundpp.h"

spp::Soundpp::Soundpp()
{
    this->dbconnection = new dbc::DataBaseConnection();
}

QSqlQueryModel* spp::Soundpp::getQueryModel_all()
{
    return this->dbconnection->getQueryModel_all();
}

