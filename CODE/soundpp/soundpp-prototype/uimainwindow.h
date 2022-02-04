#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include "soundppmanagement.h"

#include <QMainWindow>
#include <QDebug>

#include <QSqlQueryModel>
#include <QUrl>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include <QStandardItemModel>

#include <QShortcut>
#include "modelartistsdisplay.h"
#include "display_song_model.h"

#include <QContextMenuEvent>

#include <QItemSelection>

#include "uieditsongdialog.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum ModelDisplay{
        DisplayTitles = 0, DisplayArtists, DisplayAlbums
    };

    ModelDisplay getDisplayState() const;
    void setDisplayState(const ModelDisplay &value);

private slots:

    void updateGui(); // :TODO
    void onCustomContextMenu(const QPoint &point);
    void onCustomContextMenu_2(const QPoint &point);
    void addToPlaylist();
    void addToQueue();
    void display_tree();

    //musik player
    void on_btn_play_clicked();
    void on_sldr_progress_sliderMoved(int position);
    void on_sldr_volume_sliderMoved(int volume);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);
    void on_btn_volume_clicked(bool checked);

//    void on_btn_play_clicked(bool checked);
    // actions
    void on_songs_tableView_doubleClicked();
    void on_actionRemove_Song_triggered();
    void tableSelectionChanged(const QItemSelection &selected);
    void on_actionEdit_Song_triggered();
    void on_actionPlay_triggered();
    void on_actionPlay_Next_triggered();
    void on_artists_tableView_clicked(const QModelIndex &index);

    void on_btn_for_clicked();

    void on_insert_search_textChanged(const QString &arg1);

    void on_btn_titles_clicked();

    void on_btn_artists_clicked();

    void on_btn_albums_clicked();

private:
    Ui::MainWindow *ui;
    Management::SoundppManagement *sppm;

    // drag and drop
    void dragEnterEvent(QDragEnterEvent *e);
    bool filterFilesByPrefix(const QUrl &url);
    void dropEvent(QDropEvent *e);


    //displaying models
    ModelDisplay m_displayModels;
    display_artist_model* m_display_artist_model;
    display_song_model* m_display_song_model;
    display_song_model* m_m_display_song_model;
    QMenu* contextMenu;
    QMenu* contextMenu_2;
    QMenu* contextMenuHeader;

    // dbconnection

};
#endif // UIMAINWINDOW_H
