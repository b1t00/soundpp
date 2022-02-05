#include "playlistdialog.h"
#include "ui_playlistdialog.h"

playlistdialog::playlistdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playlistdialog)
{
    ui->setupUi(this);
}

playlistdialog::~playlistdialog()
{
    delete ui;
}

void setPlaylistName(QString name){

}
void setPlaylistGenre(QString genre){

}

QString playlistName()  {

}
QString playlistGenre() {

}


