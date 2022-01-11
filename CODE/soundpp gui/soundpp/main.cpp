#include "mainwindow.h"

#include <QApplication>
#include <QPushButton>

#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //set new theme

    QFile styleSheetFile("C:/Users/dreck/Documents/GitHub/soundpp/soundpp/Diffnes.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);


    MainWindow w;
    w.show();
    return a.exec();
}
