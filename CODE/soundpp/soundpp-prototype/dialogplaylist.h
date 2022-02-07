#ifndef DIALOGPLAYLIST_H
#define DIALOGPLAYLIST_H

#include <QDialog>
#include "playlist.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();


    void setPlaylistName(const Model::Playlist playlist);

    Model::Playlist getPlaylist() const;
    QString playlistName() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog *ui;
    Model::Playlist m_playlist;
};

#endif // DIALOGPLAYLIST_H
