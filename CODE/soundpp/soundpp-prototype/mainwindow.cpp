#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    qDebug() << "erstelle soundpp";
    this->spp = new spp::Soundpp();
    QSqlQueryModel *qm = spp->getQueryModel_all();
    ui->tableView->setModel(qm);

    this->mpc = new mp::MusikPlayer(this);

    connect(this->mpc, &mp::MusikPlayer::durationChanged, this, &MainWindow::on_durationChanged);
    connect(this->mpc, &mp::MusikPlayer::positionChanged, this, &MainWindow::on_positionChanged);

    this->mdp = new mp::MetaDataPlayer();
//    this->mdp->setMedia()

//connect(m_player, &QMediaPlayer::mediaStatusChanged, this, &Dialog::onMediaStatusChanged);
//    connect(this->mdp, &mp::MetaDataPlayer::)
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
// musikplayer <
