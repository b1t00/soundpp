#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDebug>
#include <QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->sqlitedb = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/dbstuff.db";

    sqlitedb.open();
    sqlitedb.setDatabaseName(dbPath);
    QSqlQueryModel *qm = new QSqlQueryModel();
    qm->setQuery("CREATE TABLE blaaa (bla TEXT, id TEXT);");
    sqlitedb.close();

    qDebug() << dbPath;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//    sqlitedb.setDatabaseName("C:/Users/Winny/Code_Local/Repositories/musikplayer-3000/z_tutorials/sqlite_connect/dbstuff.db");
    if(sqlitedb.open()){
//        QMessageBox::information(this,"Note connected", "Connected");
        QSqlQueryModel *qm = new QSqlQueryModel();
//        qm->setQuery("CREATE TABLE blaaa (bla TEXT, id TEXT);");
//        qm->setQuery("CREATE TABLE blib (bla TEXT, id TEXT);");
        qm->setQuery("SELECT * FROM blaaa");
//        qm.
        sqlitedb.close();
        std::cout << qm->rowCount() << std::endl;

        ui->tableView->setModel(qm);

    } else {
        QMessageBox::information(this,"Note connected", "Data Base Not Connected");

    }

}

void MainWindow::on_btn_save_clicked()
{
    this->sqlitedb.open();
    QString erster_wert = ui->id_text->text();
    QString zweiter_wert = ui->lineEdit_2->text();
    QString dritter_wert = ui->lineEdit_3->text();
    QSqlQuery qry;
    qInfo() << (erster_wert == NULL);
    if(erster_wert == NULL){
        qry.prepare("insert into blaaa (bla,id) values ('"+zweiter_wert+"','"+dritter_wert+"')");
        if(qry.exec()){
            qInfo() << "data id 0 is saved";
        }
    } else {
        qry.prepare("insert into tabelle1 (id,name,album) values ('"+erster_wert+"','"+zweiter_wert+"','"+dritter_wert+"')");
        if(qry.exec()){
            qInfo() << "data is saved";
        }
    }
    this->sqlitedb.close();
    on_pushButton_clicked();
}
