#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->sppm = new Management::SoundppManagement(this);

    connect(sppm, &Management::SoundppManagement::durationChanged, this, &MainWindow::on_durationChanged);
    connect(sppm, &Management::SoundppManagement::positionChanged, this, &MainWindow::on_positionChanged);

    setAcceptDrops(true);
    set_songs_tableView();


}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::readMetaData()
//{
//    qDebug() << "------------------------";
////    QString trackName = metadatareader->metaData(QMediaMetaData::Title).toString();
////    QString albumName = metadatareader->metaData(QMediaMetaData::AlbumTitle).toString();
////    QString artistName = metadatareader->metaData(QMediaMetaData::AlbumArtist).toString();

//    qDebug() << "trackName :" << trackName;
//    qDebug() << "albumName :" << albumName;
//    qDebug() << "artistName :" << artistName;
//}

void MainWindow::updateGui() //TODO::
{

}


// musikplayer >
void MainWindow::on_btn_play_clicked()
{
    bool isPlaying = sppm->pressPlay();
//    QString sppm->songName(); //TODO::

    isPlaying ? ui->statusbar->showMessage("playing song", 3000) : ui->statusbar->showMessage("pause song", 3000);

}

void MainWindow::on_sldr_progress_sliderMoved(int position)
{
    sppm->setPosition(position);
}

void MainWindow::on_sldr_volume_sliderMoved(int volume)
{
    sppm->setVolume(volume);
}

void MainWindow::on_positionChanged(qint64 position)
{
    ui->sldr_progress->setValue(position);
}

void MainWindow::on_durationChanged(qint64 duration)
{
    ui->sldr_progress->setMaximum(duration);
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
        QUrl filePath(fileName);
        qDebug() << fileName << " dropped";
//        QString queryStringInsert = "INSERT INTO songsTable (songPath) \
//                                                    VALUES (" + filePath + "));";
        QString queryStringInsert = "insert into songsTable (songPath) values ('"+filePath.toString()+"')";
//        spp->insertQuery(queryStringInsert); //TODO


    }
    set_songs_tableView();
}

void MainWindow::set_songs_tableView()
{
    QSqlQueryModel *qm = sppm->getQueryModel_all();
    ui->songs_tableView->setModel(qm);
}
