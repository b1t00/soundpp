#include <QCoreApplication>
#include <QDebug>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTime qtim;
    qtim.msecsSinceStartOfDay();
    qint64 now = QDateTime::currentMSecsSinceEpoch();
    QString number = QString::number(now);
    QString texttest = QString::number(QDateTime::currentMSecsSinceEpoch());
    qint64 wiedernow = number.toLongLong();
    qDebug() << number;
    qDebug() << texttest;
    qDebug() << wiedernow;
    qDebug() << QDateTime::fromMSecsSinceEpoch( now );
    qDebug() << "1910 : " <<QDateTime::fromMSecsSinceEpoch(  -1891396841000 );

    return a.exec();
}
