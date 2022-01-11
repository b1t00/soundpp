#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "erstelle soundpp";
    spp = new Soundpp();
    QSqlQueryModel *qm = spp->getQueryModel_all();
    ui->tableView->setModel(qm);
}

MainWindow::~MainWindow()
{
    delete ui;
}

