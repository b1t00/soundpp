#include "playlistdialog.h"
#include "ui_playlistdialog.h"
#include "playlist.h"
#include <QDebug>

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
    m_playlist.setPlaylistName(ui->playlist_name->text());
    qDebug() << "Neue Playlist erstellt : " + m_playlist.getPlaylistName();
}

Model::Playlist playlistdialog::getPlaylist() const {
    return m_playlist;
}


