#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
#include "display_artist_model.h"
#include "display_song_model.h"

#include <QContextMenuEvent>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void updateGui(); // :TODO
    void set_songs_tableView();
    void set_artists_tableView();
    void onCustomContextMenu(const QPoint &point);
    void addToPlaylist();
    void addToQueue();
    void print_out();
    void yeah();
    void display_tree();

    //musik player
    void on_btn_play_clicked();
//    void on_btn_play_toggled(bool checked);
    void on_sldr_progress_sliderMoved(int position);
    void on_sldr_volume_sliderMoved(int volume);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);


    void on_btn_play_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    Management::SoundppManagement *sppm;

    // drag and drop
    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

    //display stuff
    display_artist_model* m_display_artist_model;
    display_song_model* m_display_song_model;
    QMenu* contextMenu;

    // dbconnection

};
#endif // MAINWINDOW_H
