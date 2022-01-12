#include "databaseconnection.h"
#include <QMessageBox>

dbc::DataBaseConnection::DataBaseConnection()
{
    this->sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/dbstuff.db";
    sqlitedb.setDatabaseName(dbPath);

    if(sqlitedb.open()){
//        QMessageBox::information(this,"Note connected", "Connected");
        QSqlQueryModel *qm = new QSqlQueryModel();
        qInfo() << "db connected";
//        qm->setQuery("CREATE TABLE blaaa (bla TEXT, id TEXT);");
        qm->setQuery("CREATE TABLE interpreten (id TEXT, name TEXT, album_id TEXT);");
//        qm->setQuery("SELECT * FROM tabelle1");
//        ui->tableView->setModel(qm);
        sqlitedb.close();
//        std::cout << qm->rowCount() << std::endl;

    } else {
//        QMessageBox::information(this,"Note connected", "Data Base Not Connected");
        qDebug() << "not connted";
    }


}

QSqlQueryModel* dbc::DataBaseConnection::getQueryModel_all()
{
    bool open_success;
//    this->sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
//    QString dbPath = QCoreApplication::applicationDirPath() + "/dbstuff.db";
//    sqlitedb.setDatabaseName(dbPath);
    open_success = sqlitedb.open();
    QSqlQueryModel *qm = new QSqlQueryModel();
    qInfo() << "db get query connected " << open_success;
    qm->setQuery("SELECT * FROM interpreten");
    sqlitedb.close();
    return qm;

}
