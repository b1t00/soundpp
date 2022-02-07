#include "dialogplaylist.h"
#include <QDebug>
#include <QRandomGenerator>
#include <ui_dialogplaylist.h>
#include "playlist.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

Model::Playlist Dialog::getPlaylist() const
{
    return m_playlist;
}


void Dialog::on_buttonBox_accepted()
{
    int random_number = QRandomGenerator::global()->generate();
    if(random_number < 0){
        random_number = random_number * -1;
    }
    m_playlist.setPlaylistName(ui->playlist_name->text());
    m_playlist.setPlaylistID(random_number * -1);
}
