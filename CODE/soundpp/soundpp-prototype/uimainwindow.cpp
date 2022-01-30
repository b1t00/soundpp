#include "uimainwindow.h"
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
    //set_songs_tableView();
    display_tree();
    //set_artists_tableView();


    m_display_artist_model = new display_artist_model(sppm->create_and_get_artists(), this);
    ui->artists_tableView->setModel(m_display_artist_model);

    m_display_song_model = new display_song_model(sppm->create_and_get_songs(), this);
    ui->songs_tableView->setShowGrid(false);
    ui->songs_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->songs_tableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    contextMenu = new QMenu(ui->songs_tableView);
    contextMenuHeader = new QMenu(ui->songs_tableView->horizontalHeader());
    contextMenuHeader->addAction("blub next", this, SLOT(addToQueue()));
    contextMenu->addAction("add to Playlist", this, SLOT(addToPlaylist(const QModelIndex &index)));
    contextMenu->addAction("play next", this, SLOT(addToQueue()));
    contextMenu->addAction("remove song", this, SLOT(on_actionRemove_Song_triggered()));
    connect(ui->songs_tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));
    connect(ui->songs_tableView->horizontalHeader(), SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    ui->songs_tableView->setModel(m_display_song_model);
    ui->songs_tableView->setColumnHidden(1,true);

    ui->songs_tableView->clearSelection();
    ui->actionRemove_Song->setEnabled(false);

    //yeah();

    //print_out();


    // shortcuts
   QShortcut *sc_playPause = new QShortcut(Qt::Key_Space, this);
   connect(sc_playPause, &QShortcut::activated, this, &MainWindow::on_btn_play_clicked);

    //Icons

    QPixmap logo (":img/logo.png");
    ui->logo->setPixmap(logo);

    QPixmap volume (":img/volume.png");
    ui->volume->setPixmap(volume);

    QPixmap lupe (":img/suche_lupe.png");
    ui->lupe->setPixmap(lupe);

//    QPixmap queue (":img/queue.png");
//    ui->queue->setPixmap(queue);
     connect(ui->songs_tableView->selectionModel(),&QItemSelectionModel::selectionChanged,this, &MainWindow::tableSelectionChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateGui() //TODO::
{

}


// musikplayer >
void MainWindow::on_btn_play_clicked()
{

    bool isPlaying = false;


    isPlaying = sppm->pressPlay();
//    QString sppm->songName(); //TODO::
    sppm->incrementPlayCount();




    isPlaying ? ui->statusbar->showMessage("playing song", 3000) : ui->statusbar->showMessage("pause song", 3000);
    //set_songs_tableView(); // TODO:: Schlau direkt aus tableView zu holen

    if (!isPlaying){
        QPixmap play (":img/Play.png");
//        ui->btn_play->setIcon(play);
    } else {
        QPixmap pause (":img/pause.png");
//        ui->btn_play->setIcon(pause);
    }


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

//    qDebug() <<  "Dropt " << e->mimeData()->urls().size() << " Files.";
//    e->mimeData()->urls().size() == 1 ? ui->statusbar->showMessage("", 3000) : ui->statusbar->showMessage("pause song", 3000);

    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString filePath (url.toLocalFile());
        ui->statusbar->showMessage(filePath + " dropped", 3000);
//        qDebug() << filePath << " dropped";
        sppm->droppedFile(filePath);
    }
    set_songs_tableView();
}

void MainWindow::set_songs_tableView()
{
    QSqlQueryModel *qm = sppm->getQueryModel_all();
    ui->songs_tableView->setModel(qm);
}

void MainWindow::set_artists_tableView() {
    QSqlQueryModel *qm  = sppm->get_all_artists_direct_from_database();
    ui->artists_tableView->setModel(qm);

    qm->setHeaderData(0, Qt::Horizontal, tr("Artists"));
    qm->setHeaderData(0, Qt::Vertical, tr("Artists"));

}

void MainWindow::print_out(){

    qInfo() << sppm->get_all_Interprets();

}

void MainWindow::yeah(){
    sppm->create_and_get_artists();
}

void MainWindow::onCustomContextMenu(const QPoint &point)
{
     contextMenu->exec(ui->songs_tableView->viewport()->mapToGlobal(point));

}

void MainWindow::addToPlaylist(const QModelIndex &index){

//    qInfo() << index.model()->index(0,0);
    qInfo() << "Geil geil Geil";
}

void MainWindow::addToQueue(){
    int index = ui->songs_tableView->currentIndex().row();
    qInfo() << ui->songs_tableView->model()->index(index,1).data().toString();
    qInfo() << "Noch geiler geiler geiler";
}

void MainWindow::display_tree(){


    QStandardItemModel* playlist = new QStandardItemModel();

    QStandardItem* item0 = new QStandardItem("1 first item");
    QStandardItem* item1 = new QStandardItem("2 second item");
    QStandardItem* item3 = new QStandardItem("3 third item");
    QStandardItem* item4 = new QStandardItem("4 forth item");

    playlist->appendRow(item0);
    item0->appendRow(item3);
    item0->appendRow(item4);
    playlist->appendRow(item1);

    ui->playlist_treeView->setModel(playlist);
}

void MainWindow::on_songs_tableView_doubleClicked(const QModelIndex &index)
{
//    int index = ui->songs_tableView->currentIndex().row();
    QString songPath = ui->songs_tableView->model()->index(index.row(),1).data().toString();
//    qDebug() << song
    sppm->doubleclickPlay(songPath);
}

void MainWindow::on_actionRemove_Song_triggered()
{
    QString songName = ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),0).data().toString();
    QString songPath = ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),1).data().toString();
    QModelIndex index = ui->songs_tableView->currentIndex();
    if(index.row() >= 0 && index.row() < m_display_song_model->rowCount()){
        if(QMessageBox::question(this, "Remove: "+ songName, "Do you really want to remove \"" + songName + "\" ?","Yes","No")== 0){
            m_display_song_model->removeRow(index.row());
            sppm->deleteSong(songPath);
            ui->statusbar->showMessage("remove " + songName, 10000);
        }
    }
}

void MainWindow::tableSelectionChanged(const QItemSelection &selected)
{
    bool anySelected = selected.indexes().size() > 0; // TODO:: nur blau selected??
//    bool anySelected = selected.
    qDebug() << "any selected" <<selected.indexes().size();
    ui->actionRemove_Song->setEnabled(anySelected);
//    ui->actionRemove_Song->setVisible(anySelected);
}