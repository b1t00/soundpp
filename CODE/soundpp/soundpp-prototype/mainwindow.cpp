#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);
//    qDebug() << "erstelle soundpp";
    this->spp = new spp::Soundpp();
    QSqlQueryModel *qm = spp->getQueryModel_all();
    ui->tableView->setModel(qm);

    this->mpc = new mp::MusikPlayer(this);
    mpc->

    connect(this->mpc, &mp::MusikPlayer::durationChanged, this, &MainWindow::on_durationChanged);
    connect(this->mpc, &mp::MusikPlayer::positionChanged, this, &MainWindow::on_positionChanged);

    this->mdp = new mp::MetaDataPlayer(this);
    this->mdp->setMedia(QUrl("C:/Users/Winny/Desktop/musiktest/1914 Frank Ocean Blonde 2016 320/CAPAJEBO (C) 1914/01 Nikes.mp3"));




    metadatareader = new QMediaPlayer(this);
    connect(metadatareader,&QMediaPlayer::mediaStatusChanged,this, &MainWindow::readMetaData); // fail
    connect(mdp, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onMediaStatusChanged); // fail
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readMetaData()
{


    qDebug() << "------------------------";
    QString trackName = metadatareader->metaData(QMediaMetaData::Title).toString();
    QString albumName = metadatareader->metaData(QMediaMetaData::AlbumTitle).toString();
    QString artistName = metadatareader->metaData(QMediaMetaData::AlbumArtist).toString();

    qDebug() << "trackName :" << trackName;
    qDebug() << "albumName :" << albumName;
    qDebug() << "artistName :" << artistName;
        }
//    this->metadatareader->


// musikplayer >
void MainWindow::on_btn_play_clicked()
{
    this->mpc->play_song();
}

void MainWindow::on_sldr_progress_sliderMoved(int position)
{
    qDebug() << "position" << position;
    this->mpc->setPosition(position);
}

void MainWindow::on_sldr_volume_sliderMoved(int volume)
{
    this->mpc->setVolume(volume);
}

void MainWindow::on_positionChanged(qint64 position)
{
    ui->sldr_progress->setValue(position);
}

void MainWindow::on_durationChanged(qint64 duration)
{
    ui->sldr_progress->setMaximum(duration);
}

void MainWindow::onMediaStatusChanged(mp::MetaDataPlayer::MediaStatus status)
{
        if (status == QMediaPlayer::LoadedMedia){
            qDebug() << "meta daten wurden geladen";
            QString trackName = mdp->metaData(QMediaMetaData::Title).toString();
            QString albumName = mdp->metaData(QMediaMetaData::AlbumTitle).toString();
            QString artistName = mdp->metaData(QMediaMetaData::AlbumArtist).toString();

            qDebug() << "trackName :" << trackName;
            qDebug() << "albumName :" << albumName;
            qDebug() << "artistName :" << artistName;
        }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }

}

void MainWindow::dropEvent(QDropEvent *e)
{

    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString fileName = url.toLocalFile();
        qDebug() << fileName << " dropped";
        metadatareader->setMedia(QUrl(fileName));

    }
}
// musikplayer <
