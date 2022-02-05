#ifndef PLAYLISTDIALOG_H
#define PLAYLISTDIALOG_H

#include <QDialog>
#include "modelsong.h"
#include "playlist.h"

namespace Ui {
class playlistdialog;
}

class playlistdialog : public QDialog
{
    Q_OBJECT

public:
    explicit playlistdialog(QWidget *parent = nullptr);
    ~playlistdialog();

    void setPlaylistName(const Model::Playlist playlist);

    Model::Playlist getPlaylist() const;
    QString playlistName() const;



private slots:

    void on_accept_playlist_clicked();

private:
    Ui::playlistdialog *ui;
    Model::Playlist m_playlist;
};

#endif // PLAYLISTDIALOG_H
