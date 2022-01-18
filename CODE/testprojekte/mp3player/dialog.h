#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMediaPlayer>
#include <QFileInfo>
#include <QDebug>
#include <QUrl>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

#include <QShortcut>


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_slider_progress_sliderMoved(int position);
    void on_slider_volume_sliderMoved(int position);
    void on_pb_start_clicked();
    void on_pb_stop_clicked();
    void on_position_changed(qint64 position);
    void on_duration_changed(qint64 position);
    void on_lineEdit_textChanged(const QString &arg1);
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void GetMetaData(QMediaPlayer *player);

//protected:

private:
    Ui::Dialog *ui;
    QMediaPlayer* player;
    QMediaPlayer* m_player;

    void dragEnterEvent(QDragEnterEvent *e);
    void dropEvent(QDropEvent *e);

    QString song_path;
};
#endif // DIALOG_H
