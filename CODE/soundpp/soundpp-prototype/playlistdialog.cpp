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


void playlistdialog::on_accept_playlist_clicked()
{
    int random_number = QRandomGenerator::global()->generate();
    m_playlist.setPlaylistName(ui->playlist_name->text());
    m_playlist.setPlaylistID(random_number * -1);
    qDebug() << random_number;
    qDebug() << "Neue Playlist erstellt : " + m_playlist.getPlaylistName();
}

Model::Playlist playlistdialog::getPlaylist() const {
    return m_playlist;
}


