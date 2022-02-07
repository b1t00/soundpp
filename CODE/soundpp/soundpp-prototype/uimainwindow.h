#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include "soundppmanagement.h"

#include <QMainWindow>
#include <QDebug>

#include <QSqlQueryModel>
#include <QUrl>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMediaPlayer>
#include <QMimeData>

#include <QStandardItemModel>

#include <QShortcut>
#include "modeldisplaysongs.h"
#include "modeldisplayartists.h"
#include "modeldisplayalbums.h"
#include "displayplaylistmodel.h"

#include <QContextMenuEvent>

#include <QItemSelection>

#include "uieditsongdialog.h"
#include "playlistdialog.h"
#include "dialogplaylist.h"
#include "modelqueuelist.h"
#include "modelhistorylistl.h"

//TODO:: unused paramaters (was hat Last da nochmal gemacht?)


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum Displaystate : unsigned char{
        DisplayTitles = 0, DisplayArtists, DisplayAlbums
    };

    Displaystate getDisplayState() const;
    void setDisplayState(const Displaystate &value);

private slots:

    void updateGui(); // :TODO Maybe Catch function

    // trigger context Menus
    void onSongTableContextMenu(const QPoint &point);
    void onAttributeTableContextMenu(const QPoint &point);
    void onCustomContextMenu_2(const QPoint &point);

    void addToPlaylist();

    //musikplayer
    void on_sldr_progress_sliderMoved(int position);
    void on_sldr_volume_sliderMoved(int volume);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);
    void on_btn_volume_clicked(bool checked);
    void on_playerstatusChanged(QMediaPlayer::MediaStatus status);

    void playSong(Model::Song song_to_play);

    // musikplayer buttons
    void on_btn_play_clicked();
    void on_btn_for_clicked();

    void on_btn_for_released();
    void on_btn_back_released();

    // actions SongTable
    void on_songs_tableView_doubleClicked();
    void on_actionRemove_Song_triggered();
    void on_actionEdit_Song_triggered();
    void on_actionPlay_triggered();
    void on_actionPlay_Next_triggered();    
    void on_actionAppend_Queue_triggered();

    // actions AtributeTalble
    void on_artists_tableView_clicked(const QModelIndex &index);
    void on_artists_tableView_doubleClicked(const QModelIndex &index);
    void on_artists_tableView_activated(const QModelIndex &index); // TODO:: wann?
    void on_actionPlay_Songs_triggered();
    void on_actionPlay_Songs_Next_triggered();
    void on_actionAppend_Songs_Queue_triggered();

    // actiond view
    void on_actionDarkmode_triggered(bool checked);

    // actions Playlst
    void createNewPlaylist();
    void deletePlaylist();

    void tableSelectionChanged(const QItemSelection &selected);


    // search functions
    void on_insert_search_textChanged(const QString &arg1);

    // views get triggert
    void on_btn_titles_clicked();
    void on_btn_artists_clicked();
    void on_btn_albums_clicked();

    // insert new files
    void insertNewPaths(QList<QString> path);
    void on_actionOpen_triggered();
    void on_comboBox_activated(const QString &arg1);

private:
    Ui::MainWindow *ui;

    Management::SoundppManagement *sppm;
    Model::Song m_current_playing_song;

    // drag and drop
    void dragEnterEvent(QDragEnterEvent *e);
    bool filterFilesByPrefix(QString songPath);
    void dropEvent(QDropEvent *e);


    //displaying models
    Displaystate m_displayState; // Enum for state of display
    Model::DisplaySongModel* m_display_song_model;
    Model::DisplayArtistsModel* m_display_artist_model;
    Model::DisplayAlbumsModel* m_display_albums_model;
    Model::DisplayPlaylistModel* m_display_playlist_model;
    Model::QueueListModel *m_queueListModel;
    Model::HistoryListModel *m_historyListModel;

    QString currentSelectedAttribute() const ;
    Model::Song currentSlectedSong() const;
    QList<Model::Song> currentSlectedSongs() const;

//    QString currentSelectedAlbum() const ;

    // contex Menus
    QMenu* songTableContextMenu;
    QMenu* m_attributeTableContextMenu;
    QMenu* songTableHeaderContextMenu;
    QMenu* contextMenu_2;

    // dbconnection

};
#endif // UIMAINWINDOW_H
