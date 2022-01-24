#include "mainwindow.h"
#include <QTime>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTime qtim;
    qtim.msecsSinceStartOfDay();
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    QString number = QString::number(now);

    qint64 wiedernow = number.toLongLong();
    qDebug() << number;
    qDebug() << wiedernow;
    qDebug() << QDateTime::fromMSecsSinceEpoch( now );
    w.show();
    return a.exec();
}
