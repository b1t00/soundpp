#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QSqlQueryModel>
#include "soundpp.h"
#include "musikplayer.h"
#include "metadataplayer.h"

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

    //musik player >
    void on_btn_play_clicked();
//    void on_btn_play_toggled(bool checked);
    void on_sldr_progress_sliderMoved(int position);
    void on_sldr_volume_sliderMoved(int volume);
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);
    //musik player <

private:
    Ui::MainWindow *ui;
    spp::Soundpp *spp;
    mp::MusikPlayer *mpc;
    mp::MetaDataPlayer *mdp;

};
#endif // MAINWINDOW_H
