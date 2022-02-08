#ifndef ADDTOPLAYLISTDIALOG_H
#define ADDTOPLAYLISTDIALOG_H

#include <QDialog>
#include <playlist.h>
#include <displayplaylistmodel.h>
#include <soundppmanagement.h>

namespace Ui {
class addToPlaylistDialog;
}

class addToPlaylistDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addToPlaylistDialog(QWidget *parent = nullptr);
    ~addToPlaylistDialog();

    QString getPlaylistName();


private slots:
    void on_buttonBox_accepted();

private:


    Ui::addToPlaylistDialog *ui;

    Model::DisplayPlaylistModel* m_display_playlist_model;

    Management::SoundppManagement *sppm;
};

#endif // ADDTOPLAYLISTDIALOG_H
