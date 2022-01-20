#include "dialog.h"
#include "ui_dialog.h"
#include "QMediaMetaData"
#include <QMediaObject>
//#include <>
#include <QAudioDecoder>
#include <QAudio>
#include <QVariant>




Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    player = new QMediaPlayer(this);
    this->m_player = new QMediaPlayer(this);

//    connect(m_player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &Dialog::onMediaStatusChanged);

    bool pstate = QMediaPlayer::PausedState;
    qDebug() << "bool " << pstate;
    connect(player, &QMediaPlayer::positionChanged, this, &Dialog::on_position_changed);
    connect(player, &QMediaPlayer::durationChanged, this, &Dialog::on_duration_changed);

    QShortcut *start_sc = new QShortcut(Qt::Key_Space, this);
    connect(start_sc, &QShortcut::activated, this, &Dialog::on_pb_start_clicked);

    song_path = "C:/Users/Winny/Music/Musik/Interpreten/Frank Ocean/1914 Frank Ocean Blonde 2016 320/CAPAJEBO (C) 1914/01 Nikes.mp3";

    QPixmap pix("C:/Users/Winny/Music/Musik/Claudi Usb Stick/1979 - Joy Division - Unknown Pleasures [HDTracks 24-192 FLAC]/cover.jpg");
    ui->cover_label->setPixmap(pix);

//    player->Meta

    QFileInfo *fi = new QFileInfo(song_path);
//    fi->metaObject()->className();
//    ui->lineEdit->setText(fi.fileName());

//   QMultiMedia au;

//    QString artistName = player->metaData(QMediaMetaData::AlbumArtist).toString();
//    qDebug() << "artistname:" << artistName;
//    qDebug() << artist

//    QString arti =  "nöa";
    QVariant *qvj = new QVariant(QUrl(song_path));
    qDebug() << " keine Ahnugn " << qvj->BitArray->toString();

//    qDebug() << "album artist: " <<  qv.Line;

    // ------------- meta test


    setAcceptDrops(true);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_slider_progress_sliderMoved(int position)
{
    player->setPosition(position);
}

void Dialog::on_slider_volume_sliderMoved(int position)
{
    player->setVolume(position);
}

void Dialog::on_pb_start_clicked()
{

    QUrl songi = QUrl::fromLocalFile(this->song_path);
    player->setMedia(songi);
    player->play();
    qDebug() << player->errorString();
//    qDebug() << player->metaData(songi,QMediaPlayer::key);
    QVariant qv = player->metaData(QMediaMetaData::MediaType);
//    QMetaObject qmo = player->availableMetaData();
//    qDebug() << "album artist: " <<  player->availableMetaData().value(1);

    qInfo() << "-----------------------------------";
    qInfo() << "player->isMetaDataAvailable(): " << player->isMetaDataAvailable();
    if(player->isMetaDataAvailable()){

    QString trackName = player->metaData(QMediaMetaData::Title).toString();
    QString albumName = player->metaData(QMediaMetaData::AlbumTitle).toString();
    QString artistName = player->metaData(QMediaMetaData::AlbumArtist).toString();
//    QImage coverArtworkqImage = player->metaData(QMediaMetaData::CoverArtImage).value<QImage>();
    qInfo() << "Track name: " << trackName;
    qInfo() << "Album name: " << albumName;
    qInfo() << "Artist name: " << artistName;
//    qInfo() << "cover format " << coverArtwork.format();
//    qInfo() << "cover format " << coverArtwork.convertTo("png", );

    QString albumcoverpath = song_path;
    QString test = "C:/Users/Winny/Music/Musik/Interpreten/Frank Ocean/1914 Frank Ocean Blonde 2016 320/CAPAJEBO (C) 1914/cover.jpg";
    qDebug() << albumcoverpath;
    albumcoverpath.chop(songi.fileName().length());
    albumcoverpath.append("cover.jpg");
    qDebug() << albumcoverpath;
    qDebug() << test;
    QPixmap coverArtworkpixmap(albumcoverpath);
    ui->cover_label->setPixmap(albumcoverpath);

    qDebug() << albumcoverpath;
//    QPixmap coverArt(song)

//    ui->cover_label->setPixmap(coverArtworkpixmap);
//    ui->cover_label->setPixmap(QPixmap::fromImage(coverArtworkqImage));
    }
}
//}

void Dialog::on_pb_stop_clicked()
{
    player->pause();
}

void Dialog::on_position_changed(qint64 position)
{
    ui->slider_progress->setValue(position);
}

void Dialog::on_duration_changed(qint64 position)
{
    ui->slider_progress->setMaximum(position);
}

void Dialog::on_lineEdit_textChanged(const QString &arg1)
{
    //    ui
}

void Dialog::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    qDebug() <<" metadata available";
    if (status == QMediaPlayer::LoadedMedia)
        GetMetaData(m_player);
}

void Dialog::GetMetaData(QMediaPlayer *player)
{
    // Get the list of keys there is metadata available for
    QStringList metadatalist = player->availableMetaData();

    // Get the size of the list
    int list_size = metadatalist.size();

    //qDebug() << player->isMetaDataAvailable() << list_size;

    // Define variables to store metadata key and value
    QString metadata_key;
    QVariant var_data;

    for (int indx = 0; indx < list_size; indx++)
    {
      // Get the key from the list
      metadata_key = metadatalist.at(indx);

      // Get the value for the key
      var_data = player->metaData(metadata_key);

     qDebug() << metadata_key << var_data.toString();
    }
}

void Dialog::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }
}

void Dialog::dropEvent(QDropEvent *e){
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();

        this->m_player->setMedia(QUrl::fromLocalFile(fileName));

//        QMediaObject song_meta();
//        song_meta().isMetaDataAvailable();
//        QAudioDecoder song_dev;
//        QVariant qv(fileName);
//        qv.data();

        this->song_path = fileName;

        ui->lineEdit->setText(fileName);
        qDebug() << "Dropped file:" << fileName;
    }
}

