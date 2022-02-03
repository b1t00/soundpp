#include "uimainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);
    this->sppm = new Management::SoundppManagement(this);

    connect(sppm, &Management::SoundppManagement::durationChanged, this, &MainWindow::on_durationChanged);
    connect(sppm, &Management::SoundppManagement::positionChanged, this, &MainWindow::on_positionChanged);

    display_tree();

    m_displayModels = DisplayArtists;

    //Display & Interact ArtistModel
    m_display_artist_model = new display_artist_model(sppm->allArtists(),this);
    ui->artists_tableView->setModel(m_display_artist_model);


    //Display & Interact SongModel
//    m_display_song_model = new display_song_model(sppm->get_all_songs(), this);
    ui->songs_tableView->setShowGrid(false);
    ui->songs_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->songs_tableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    contextMenu = new QMenu(ui->songs_tableView);
    contextMenu->addAction("play next", this, SLOT(addToQueue()));
//    contextMenu->addAction("add to Playlist", this, SLOT(addToPlaylist(const QModelIndex &index)));
    contextMenu->addAction("remove song", this, SLOT(on_actionRemove_Song_triggered()));
    contextMenu->addAction("edit song...", this, SLOT(on_actionEdit_Song_triggered()));
    connect(ui->songs_tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    contextMenuHeader = new QMenu(ui->songs_tableView->horizontalHeader());
    contextMenuHeader->addAction("blub next", this, SLOT(addToQueue()));
    // TODO:: connect(ui->songs_tableView->horizontalHeader(), SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));



//    ui->songs_tableView->setModel(m_display_song_model);
    ui->songs_tableView->setColumnHidden(0,true); // hide path column
    ui->songs_tableView->setColumnHidden(5,true);
    ui->songs_tableView->setColumnHidden(6,true);

    ui->songs_tableView->clearSelection();
//    ui->actionRemove_Song->setEnabled(false);




    //yeah();

    //print_out();


    // shortcuts
   QShortcut *sc_playPause = new QShortcut(Qt::Key_Space, this);
   connect(sc_playPause, &QShortcut::activated, this, &MainWindow::on_btn_play_clicked);

    //Icons

    QPixmap logo (":img/logo.png");
    ui->logo->setPixmap(logo);

    QPixmap volume (":img/volume.png");
    ui->btn_volume->setIcon(volume);

    QPixmap lupe (":img/suche_lupe.png");
    ui->lupe->setPixmap(lupe);

    QPixmap play (":img/Play.png");
    ui->btn_play->setIcon(play);

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
    if(sppm->isAudioAvailable()){

    bool isPlaying = false;

    isPlaying = sppm->pressPlay();
//    QString sppm->songName(); //TODO::
//    sppm->incrementPlayCount();

    isPlaying ? ui->statusbar->showMessage("playing song", 3000) : ui->statusbar->showMessage("pause song", 3000);
    //set_songs_tableView(); // TODO:: Schlau direkt aus tableView zu holen

    if (isPlaying){
        QPixmap pause (":img/pause.png");
        ui->btn_play->setIcon(pause);
    } else {
        QPixmap play (":img/Play.png");
        ui->btn_play->setIcon(play);
    }
    } else {
//        if(ui->songs_tableView->selectionModel()->selectedRows())
        if(ui->songs_tableView->selectionModel()->hasSelection()){
            on_songs_tableView_doubleClicked();
        } else {
            ui->statusbar->showMessage("No song selected", 5000);
        }
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

bool MainWindow::filterFilesByPrefix(const QUrl &url)
{
    QList<QString> splittingString = url.toString().split(".");
    QString filePrefix = splittingString[splittingString.size()-1].toUpper();
    if(!(filePrefix == "MP3" | filePrefix == "WAV") ){
        ui->statusbar->showMessage(filePrefix + " files are not playable, sorry", 10000);
        return false;
    }
    return true;
}

void MainWindow::dropEvent(QDropEvent *e)
{
    bool newArtist = false;
    foreach (const QUrl &url, e->mimeData()->urls()) {
        if(filterFilesByPrefix(url)){

            QString filePath (url.toLocalFile());
            ui->statusbar->showMessage(filePath + " dropped", 3000);
            Model::Song song_to_add = sppm->droppedFile(filePath);

            if(!m_display_artist_model->containsArtist(song_to_add.getArtistName())){
                newArtist = true;
            }
//            m_display_song_model->addSong(song_to_add); // TODO::
            if(newArtist){
            // if a new artist is in the dopped file, the table will reload completely because of the sorting
                m_display_artist_model = new display_artist_model(sppm->allArtists(),this);
                ui->artists_tableView->setModel(m_display_artist_model);
            }
        }
//    ui->songs_tableView->setModel(sppm->getQueryModel_all());
//    set_songs_tableView();
    }
}



void MainWindow::onCustomContextMenu(const QPoint &point)
{
     contextMenu->exec(ui->songs_tableView->viewport()->mapToGlobal(point));

}

void MainWindow::addToPlaylist(){

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

void MainWindow::on_songs_tableView_doubleClicked()
{
    QPixmap pause (":img/pause.png");
    ui->btn_play->setIcon(pause);
    QString songPath = ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),0).data().toString();
    QString songName = ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),1).data().toString();
    QString artistName = ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),2).data().toString();
    ui->current_song_label->setText(artistName + " - " + songName);
    ui->statusbar->showMessage("playing: " + songName, 3000);
    sppm->doubleclickPlay(songPath);
}


void MainWindow::on_actionPlay_triggered() // TODO:: function redundante
{
    on_songs_tableView_doubleClicked();
}

#include<algorithm>
void MainWindow::on_actionRemove_Song_triggered()
{
    QModelIndexList selection = ui->songs_tableView->selectionModel()->selectedRows();

    QString deleteMessages = "Do you really want to remove?\n";
    for(int i = 0 ; i < selection.size(); i++){
        deleteMessages += ui->songs_tableView->model()->index(selection.at(i).row(),1).data().toString() + "\n";
    }

    std::sort(selection.begin(),selection.end()); // sort to compute right indices for removing

    if(QMessageBox::question(this, "Remove song/songs", deleteMessages,"Yes","No")== 0){

        ui->statusbar->showMessage("remove " + QString::number(selection.size()) + " songs.", 10000);

        for(int i = 0 ; i < selection.size(); i++){
            int indexrow = selection.at(i).row() - i;
            QString songPath = ui->songs_tableView->model()->index(indexrow,0).data().toString();
            QString songName = ui->songs_tableView->model()->index(indexrow,1).data().toString();
            QString artistName = ui->songs_tableView->model()->index(indexrow,2).data().toString();
//            qDebug() << "selection : " << selection.at(i).row();
                if(indexrow >= 0 && indexrow < m_display_song_model->rowCount()){
                    bool removed = sppm->deleteSong(songPath);
                    if(removed){
                        m_display_song_model->removeRow(indexrow);
                    } else {
                        ui->statusbar->showMessage("could not remove " + songName, 10000);
                    }
                    if(m_display_song_model->rowCount() <= 0){
                        qDebug() << "keine songs mehr da";
//                        m_display_artist_model = new display_artist_model(sppm->allArtists(),this);
//                        ui->artists_tableView->setModel(m_display_artist_model);
                        if(m_displayModels == DisplayArtists) {
                            qDebug() << "remove arti";
                            m_display_artist_model->removeArtist(artistName);
                        } else if(m_displayModels == DisplayAlbums){

                        }

                    }
                }
            }
        }
}

void MainWindow::tableSelectionChanged(const QItemSelection &selected)
{
    bool anySelected = selected.indexes().size() > 0; // TODO:: nur blau selected??
//    bool anySelected = selected.
//    qDebug() << "any selected" <<selected.indexes().size();
//    ui->actionRemove_Song->setEnabled(anySelected);
//    ui->actionRemove_Song->setVisible(anySelected);
}

void MainWindow::on_actionEdit_Song_triggered()
{
    Model::Song song_to_edit;
    int rowIndex = ui->songs_tableView->currentIndex().row();
    song_to_edit.setSongPath(ui->songs_tableView->model()->index(rowIndex,0).data().toString());
    song_to_edit.setTitle(ui->songs_tableView->model()->index(rowIndex,1).data().toString());
    song_to_edit.setArtistName(ui->songs_tableView->model()->index(rowIndex,2).data().toString());
    song_to_edit.setAlbumName(ui->songs_tableView->model()->index(rowIndex,3).data().toString());
    song_to_edit.setAlbumNr(ui->songs_tableView->model()->index(rowIndex,4).data().toInt());
    song_to_edit.setLabelName(ui->songs_tableView->model()->index(rowIndex,5).data().toString());
    song_to_edit.setLabelNr(ui->songs_tableView->model()->index(rowIndex,6).data().toString());
    song_to_edit.setAddedTime(ui->songs_tableView->model()->index(rowIndex,7).data().toString());
    song_to_edit.setPlayCount(ui->songs_tableView->model()->index(rowIndex,8).data().toInt());
//    song_to_edit.se(ui->songs_tableView->model()->index(rowIndex,1).data().toString());
    EditSongDialog editDialog(song_to_edit,this);
    if(editDialog.exec() == QDialog::Accepted){
        m_display_song_model->updateSong(rowIndex,editDialog.song());
        // TODO:: db connection
        if(song_to_edit.getTitle() != editDialog.song().getTitle()){ // TODO:: switchcase for changed atributs
            qDebug() << song_to_edit.getTitle() << " zu " << editDialog.song().getTitle();
//            ui->statusbar->showMessage("remove " + songName, 10000);
        }
    }

}



void MainWindow::on_actionPlay_Next_triggered()
{
}

void MainWindow::on_artists_tableView_clicked(const QModelIndex &index)
{
    //inhalt wird per parameter übergeben und anhand dieses parameters wird dann die songs table vie aktualisiert

   // qInfo() << sppm->filtered_songs_by_artist(index.data().toString());

//    qInfo() << index.data();
//    qInfo() << index.data().toString();
//    sppm->filtered_songs_by_artist("Dendemann");

    m_display_song_model = new display_song_model(sppm->filtered_songs_by_artist(index.data().toString()), this);
    ui->songs_tableView->setModel(m_display_song_model);
}
void MainWindow::on_btn_volume_clicked(bool checked)
{
    sppm->press_mute(checked);

    if(checked){
        QPixmap mute (":img/mute.png");
        ui->btn_volume->setIcon(mute);
    } else {
        QPixmap volume (":img/volume.png");
        ui->btn_volume->setIcon(volume);
    }
}



void MainWindow::on_btn_for_clicked()
{

}




//void MainWindow::on_btn_search_clicked(QString search)
//{
//    qInfo() << "jhdkaue";
//    qInfo() << ui->insert_search->text();

//    qInfo() << search;

//    m_display_song_model = new display_song_model(sppm->search_result(search), this);
//    ui->songs_tableView->setModel(m_display_song_model);
//}

void MainWindow::on_insert_search_textChanged(const QString &arg1)
{

    m_display_song_model = new display_song_model(sppm->search_result(arg1), this);
    ui->songs_tableView->setModel(m_display_song_model);

}
