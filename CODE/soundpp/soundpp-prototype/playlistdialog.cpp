#include "playlistdialog.h"
#include "ui_playlistdialog.h"
#include "playlist.h"
#include <QDebug>
#include <QRandomGenerator>

playlistdialog::playlistdialog( QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playlistdialog)
{
    ui->setupUi(this);
}

playlistdialog::~playlistdialog()
{
    delete ui;
}


Model::Playlist playlistdialog::getPlaylist() const {
    return m_playlist;
}



void playlistdialog::on_buttonBox_accepted()
{
    int random_number = QRandomGenerator::global()->generate();
    if(random_number < 0){
        random_number = random_number * -1;
    }
    m_playlist.setPlaylistName(ui->playlist_name->text());
    m_playlist.setPlaylistID(random_number * -1);

    qInfo() <<"Hallo";

}
