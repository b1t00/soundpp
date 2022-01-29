#include "mainwindow.h"
#include <QTime>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //set Theme

    QFile styleSheetFile("C:/Users/dreck/Documents/GitHub/soundpp/CODE/soundpp/soundpp-prototype/Combinear.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);


    MainWindow w;
    w.show();
    return a.exec();

}

