#include "addtoplaylistdialog.h"
#include "ui_addtoplaylistdialog.h"

addToPlaylistDialog::addToPlaylistDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addToPlaylistDialog)
{
    ui->setupUi(this);
    this->sppm = new Management::SoundppManagement(this);
    m_display_playlist_model = new Model::DisplayPlaylistModel(sppm->get_all_playlists());
    ui->listView->setModel(m_display_playlist_model);



}

addToPlaylistDialog::~addToPlaylistDialog()
{
    delete ui;
}

QString addToPlaylistDialog::getPlaylistName() {

    int indexrow = ui->listView->currentIndex().row();
    QString playlistName =  ui->listView->model()->index(indexrow, 0).data().toString();
    return playlistName;

}



void addToPlaylistDialog::on_buttonBox_accepted()
{



}
