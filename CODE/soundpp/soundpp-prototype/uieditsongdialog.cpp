#include "uieditsongdialog.h"
#include "ui_editsongdialog.h"

#include <QDebug>

EditSongDialog::EditSongDialog(Model::Song song ,QWidget *parent)
    :QDialog(parent),
    ui(new Ui::EditSongDialog),
    m_song(song)
{
    ui->setupUi(this);
    m_song = song;

    ui->lineEdit_songTitle->setText(m_song.getTitle());
    ui->lineEdit_artistName->setText(m_song.getArtistName());
    ui->lineEdit_albumName->setText(m_song.getAlbumName());
    ui->lcd_songNr->setDigitCount(m_song.getAlbumNr());
}

EditSongDialog::~EditSongDialog()
{
    delete ui;
}

void EditSongDialog::on_buttonBox_accepted()
{
    m_song.setTitle(ui->lineEdit_songTitle->text());
    m_song.setArtistName(ui->lineEdit_artistName->text());
    m_song.setAlbumName(ui->lineEdit_albumName->text());}

Model::Song EditSongDialog::song() const
{
    return m_song;
}

void EditSongDialog::setSong(const Model::Song &song)
{
    m_song = song;
}
