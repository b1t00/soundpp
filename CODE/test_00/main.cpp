#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <iostream>
#include <QDebug>

void foo(){
//    std::cout << "hello QT" << std::endl;
    qDebug() << "hello QT";
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window, window2, window3;


    QPushButton *pButton = new QPushButton("Hello World", &window);
    pButton->setGeometry(10, 10, 150, 30);

    QObject::connect(pButton, &QPushButton::clicked, foo);

    QLabel *pLabel = new QLabel(&window2);
    pLabel->setGeometry(10, 10, 200, 30);
    QLineEdit *pLineEdit = new QLineEdit(&window3);
    pLineEdit->setGeometry(10, 10, 200, 30);


   if(!QObject::connect(pLineEdit, &QLineEdit::textChanged, pLabel, &QLabel::setText)){
         qDebug() << "connection failed ";
   }

    window.show();
    window2.show();
    window3.show();
    return app.exec();
}
