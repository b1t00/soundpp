#include "uimainwindow.h"
#include "ui_mainwindow.h"

#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setAcceptDrops(true);
    this->sppm = new Management::SoundppManagement(this);

    connect(sppm, &Management::SoundppManagement::durationChanged, this, &MainWindow::on_durationChanged);
    connect(sppm, &Management::SoundppManagement::positionChanged, this, &MainWindow::on_positionChanged);
    connect(sppm, &Management::SoundppManagement::playerstatusChanged, this, &MainWindow::on_playerstatusChanged);

    display_tree();

    // ---------------------- Models -------------------------- //

    // -------- SongTable Model
    m_display_song_model = new Model::DisplaySongModel(sppm->get_all_songs(), this);
    m_displayState = DisplayTitles;
    ui->songs_tableView->setModel(m_display_song_model);
    ui->songs_tableView->setColumnHidden(0,true); // hide path column
    ui->songs_tableView->setColumnHidden(5,true);
    ui->songs_tableView->setColumnHidden(6,true);
    ui->songs_tableView->clearSelection();
//    ui->songs_tableView->horizontalHeader()-> ->width();

    //--------- AtributeTable; Artist and Albums Model -
    m_display_artist_model = new Model::DisplayArtistsModel(sppm->allArtists(),this);
    ui->artists_tableView->setModel(m_display_artist_model);
    ui->artists_tableView->hide(); // hide at the start

    //----------QueueListTable; Queue and History Model -
    m_historyListModel = new Model::HistoryListModel(this);
    m_queueListModel = new Model::QueueListModel(this);
    ui->queue_tableView->setModel(m_queueListModel);

//    m_display_artist_model->headerData(2,Qt::Orientation::Horizontal)


    // ------------------- Context Menus --------------------- //

    // -- Context Menus Song Table Header-

    // TODO: Coloms hide and show
//    ui->songs_tableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
    songTableHeaderContextMenu = new QMenu(ui->songs_tableView->horizontalHeader());

    //  contextMenuHeader->addAction("todo", this, SLOT(addToQueue()));
    // connect(ui->songs_tableView->horizontalHeader(), SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    // ---- Context Menu Song Table --

    ui->songs_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    songTableContextMenu = new QMenu(ui->songs_tableView);
//    songTableContextMenu->addAction("play song", this, &MainWindow::on_actionPlay_triggered); // a bit unnecessary because doubleclick makes the same
    songTableContextMenu->addAction("play next", this, &MainWindow::on_actionPlay_Next_triggered);
    songTableContextMenu->addAction("append queuelist",this, &MainWindow::on_actionAppend_Queue_triggered);
    songTableContextMenu->addSeparator();
    songTableContextMenu->addAction("add to Playlist", this,&MainWindow::addToPlaylist);
    songTableContextMenu->addSeparator();
    songTableContextMenu->addAction("edit song...", this,&MainWindow::on_actionEdit_Song_triggered);
    songTableContextMenu->addAction("remove song", this,&MainWindow::on_actionRemove_Song_triggered);
    connect(ui->songs_tableView, &QWidget::customContextMenuRequested, this, &MainWindow::onSongTableContextMenu);
//    connect(ui->songs_tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu(const QPoint &)));

    // -------------- selection change -------------------- //
    // TODO::

    connect(ui->songs_tableView->selectionModel(),&QItemSelectionModel::selectionChanged,this, &MainWindow::tableSelectionChanged);
    connect(ui->artists_tableView->selectionModel(),&QItemSelectionModel::selectionChanged,this, &MainWindow::tableSelectionChanged);

    //Display & Interact PlaylistModel
    m_display_playlist_model = new Model::DisplayPlaylistModel(sppm->get_all_playlists());
    ui->playlist_tableView->setModel(m_display_playlist_model);

    ui->playlist_tableView->setShowGrid(false);
    ui->playlist_tableView->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->playlist_tableView->horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);


    contextMenu_2 = new QMenu(ui->playlist_tableView);
    contextMenu_2->addAction("new Playlist..", this, SLOT(createNewPlaylist()));
    contextMenu_2->addAction("delete Playlist", this, SLOT(deletePlaylist()));
    connect(ui->playlist_tableView, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(onCustomContextMenu_2(const QPoint &)));

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

}

MainWindow::~MainWindow()
{
    delete ui;
}

// ---------------- Private Helper-Methods ----------------- //

QString MainWindow::currentSelectedAttribute() const
{
    return ui->artists_tableView->model()->index(ui->artists_tableView->currentIndex().row(),0).data().toString();
}

Model::Song MainWindow::currentSlectedSong() const
{
    Model::Song s;
    s.setSongPath(ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),0).data().toString());
    s.setTitle(ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),1).data().toString());
    s.setArtistName(ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),2).data().toString());
//    QString songName = ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),1).data().toString();
//    QString artistName = ui->songs_tableView->model()->index(ui->songs_tableView->currentIndex().row(),2).data().toString();
    return s;
}

QList<Model::Song> MainWindow::currentSlectedSongs() const
{
    QModelIndexList selection = ui->songs_tableView->selectionModel()->selectedRows();
    QList<Model::Song> songs_selected;
    QString deleteMessages = "Do you really want to remove?\n";
    for(int i = 0 ; i < selection.size(); i++){
        songs_selected.append(Model::Song(
                                  ui->songs_tableView->model()->index(selection.at(i).row(),0).data().toString(),
                                  ui->songs_tableView->model()->index(selection.at(i).row(),1).data().toString(),
                                  ui->songs_tableView->model()->index(selection.at(i).row(),2).data().toString(),
                                  ui->songs_tableView->model()->index(selection.at(i).row(),3).data().toString()
                                  ));
        deleteMessages += ui->songs_tableView->model()->index(selection.at(i).row(),1).data().toString() + "\n";
    }

    return songs_selected;
}



void MainWindow::updateGui() //TODO::
{

}

// -------------------------- GUI ---------------------------//

//----------Dark Mode --------------//
void MainWindow::on_actionDarkmode_triggered(bool checked)
{

    if(checked){
    this->setStyleSheet("background-color: grey;");
        ui->artists_tableView->setAlternatingRowColors(false);
        ui->songs_tableView->setAlternatingRowColors(false);
    } else {
    this->setStyleSheet("background-color: white");
        ui->artists_tableView->setAlternatingRowColors(true);
        ui->songs_tableView->setAlternatingRowColors(true);
    }

}

// -------------- selection change -------------------- //
// TODO:: selection check dont works
void MainWindow::tableSelectionChanged(const QItemSelection &selected)
{
    bool anySelected = selected.indexes().size() > 0; // TODO:: nur blau selected??

//    qDebug() << anySelected << "any selected : " <<selected.indexes().size();
//    qDebug() << "wo selected?: " << selected.at(0);

        ui->actionRemove_Song->setEnabled(anySelected);
        ui->actionRemove_Song->setVisible(anySelected);
}


// --------------- Drag and Drop ------------------------ //
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls()) {
        e->acceptProposedAction();
    }

}

bool MainWindow::filterFilesByPrefix(QString songPath)
{
    QList<QString> splittingString = songPath.split(".");
    QString filePrefix = splittingString[splittingString.size()-1].toUpper();
    if(!(filePrefix == "MP3" | filePrefix == "WAV" | filePrefix == "AIFF") ){
        ui->statusbar->showMessage(filePrefix + " files are not playable, sorry", 10000);
        return false;
    } else if(sppm->containsSongPath(songPath)){
        ui->statusbar->showMessage(songPath + " is already in the database", 10000);
        return false;
    }
    return true;
}

void MainWindow::dropEvent(QDropEvent *e)
{
    bool newArtist, currentArtist = false;
    bool newAlbum, currentAlbum = false;
    foreach (const QUrl &url, e->mimeData()->urls()) {
        QString filePath (url.toLocalFile());
        if(filterFilesByPrefix(filePath)){

            ui->statusbar->showMessage(filePath + " dropped", 3000);
            Model::Song song_to_add = sppm->droppedFile(filePath);
            if(m_displayState == DisplayTitles){
                m_display_song_model->addSong(song_to_add);

            } else if(m_displayState == DisplayArtists){

                if(song_to_add.getArtistName() == currentSelectedAttribute()){
                    currentArtist = true;
                } else if(!m_display_artist_model->containsArtist(song_to_add.getArtistName())){
                    newArtist = true;
                }

            } else if(m_displayState == DisplayAlbums){
                qDebug() << currentSelectedAttribute();
                if(song_to_add.getAlbumName() == currentSelectedAttribute()){
                    currentAlbum = true;
                } else if(!m_display_albums_model->containsAlbum(song_to_add.getAlbumName())){
                    newAlbum = true;
                    qDebug() << song_to_add.getAlbumName() << "newAlbum? " << newAlbum;
                }
            }

        }

    }
    if(m_displayState == DisplayArtists){
    // if a new artist is in the dopped file, the atribute table will reload completely because of the sorting
        if (currentArtist){
            m_display_song_model = new Model::DisplaySongModel(sppm->filtered_songs_by_artist(currentSelectedAttribute()));
            ui->songs_tableView->setModel(m_display_song_model);
        }

        if(newArtist){
            m_display_artist_model = new Model::DisplayArtistsModel(sppm->allArtists(),this);
            ui->artists_tableView->setModel(m_display_artist_model);
        }
    } else if(m_displayState == DisplayAlbums){
        if (currentAlbum){
            qDebug()<<  "current album " << currentSelectedAttribute() << newAlbum;
            m_display_song_model = new Model::DisplaySongModel(sppm->filtered_songs_by_album(currentSelectedAttribute()));
            ui->songs_tableView->setModel(m_display_song_model);
        }
        if(newAlbum){
            m_display_albums_model = new Model::DisplayAlbumsModel(sppm->allAlbums(),this);
            ui->artists_tableView->setModel(m_display_albums_model);
        }
    }
}

// ---------------------Button - Views - Enums -------------------------//


void MainWindow::on_btn_titles_clicked()
{
    m_display_song_model = new Model::DisplaySongModel(sppm->get_all_songs(), this);
    ui->songs_tableView->setModel(m_display_song_model);
    ui->artists_tableView->hide();
    m_displayState = DisplayTitles;
}

//TODO:: last artists and albums clicked memory variable
void MainWindow::on_btn_artists_clicked()
{
    // TODO: REIN ODER RAUS?= ----->>>
    if(ui->artists_tableView->selectionModel()->selectedIndexes().size() > 0){
//        QString current_selected_artist = ui->artists_tableView->model()->index(ui->artists_tableView->currentIndex().row(),0).data().toString();
//        qDebug() << "current_selected_artist" << current_selected_artist;
         m_display_song_model = new Model::DisplaySongModel(sppm->filtered_songs_by_artist(currentSelectedAttribute()), this);
         ui->songs_tableView->setModel(m_display_song_model);
    } else {
//        ui->artists_tableView->selectRow(0);
        m_display_song_model->clear();
//        ui->songs_tableView->model()->clear();
//        m_display_song_model->set
    }

    // TODO: REIN ODER RAUS?= <...
    m_display_artist_model = new Model::DisplayArtistsModel(sppm->allArtists(),this);
    ui->artists_tableView->setModel(m_display_artist_model);
    ui->artists_tableView->show();
    m_displayState = DisplayArtists;
}

void MainWindow::on_btn_albums_clicked()
{    // very redundante to on_btn_artists_clicked(), but maybe can be adjusted to a proper albums view (covers etc)

    if(ui->artists_tableView->selectionModel()->selectedIndexes().size() > 0){
//        QString current_selected_artist = ui->artists_tableView->model()->index(ui->artists_tableView->currentIndex().row(),0).data().toString();
         m_display_song_model = new Model::DisplaySongModel(sppm->filtered_songs_by_album(currentSelectedAttribute()), this);
         ui->songs_tableView->setModel(m_display_song_model);
    } else {
        m_display_song_model->clear();
    }
    m_display_albums_model = new Model::DisplayAlbumsModel(sppm->allAlbums(),this);
    ui->artists_tableView->setModel(m_display_albums_model);
    ui->artists_tableView->show();
    m_displayState = DisplayAlbums;
}

// -------------------- context Menus ---------------------------------//

void MainWindow::onSongTableContextMenu(const QPoint &point)
{
     songTableContextMenu->exec(ui->songs_tableView->viewport()->mapToGlobal(point));

}

void MainWindow::onCustomContextMenu_2(const QPoint &point){

    contextMenu_2->exec(ui->playlist_tableView->viewport()->mapToGlobal(point));
}


// ------------------- Menu Actions -------------------------//


// --------------- Musik Player Methods ---------------------//

void MainWindow::playSong(Model::Song song_to_play)
{
    QPixmap pause (":img/pause.png");
    ui->btn_play->setIcon(pause);

    ui->current_song_label->setText(song_to_play.getArtistName() + " - " + song_to_play.getTitle());
    ui->statusbar->showMessage("playing: " + song_to_play.getArtistName(), 3000);

    sppm->playSong(song_to_play.getSongPath());
    m_historyListModel->addSong(song_to_play);
//    m_queueListModel->playSong(s);
}


void MainWindow::on_actionPlay_triggered() // TODO:: function redundante
{
    Model::Song song_selected = currentSlectedSong();
    playSong(song_selected);

}

void MainWindow::on_songs_tableView_doubleClicked()
{
    on_actionPlay_triggered();
}

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
            on_actionPlay_triggered();
        } else {
            ui->statusbar->showMessage("No song selected", 5000);
        }
    }
}


void MainWindow::on_btn_back_released()
{
    if (ui->sldr_progress->value() < 5000){
        m_historyListModel->setIndexHistory(1);
        Model::Song song_previous = m_historyListModel->songByIndex();

        playSong(song_previous);
//        m_playlist->previous();
    } else{
        ui->sldr_progress->setValue(0);
//        m_player->setPosition(0);
    }
}



void MainWindow::on_btn_for_clicked()
{
    //maybe load song?
}

void MainWindow::on_btn_for_released()
/*
 * *dont mix up whith play next method, who adds song to queue list
 * push next button for next song functionality
*/
{
    Model::Song song_next;
    if(m_queueListModel->hasSongs()){
        song_next = m_queueListModel->nextSong();
//    } else if( loopQueueList){ // TODO
//    } else if( autoPlay){ // TODO
    }
    playSong(song_next);
}


// --- Musikplayer - Sliders and Volume ---

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

void MainWindow::on_playerstatusChanged(QMediaPlayer::MediaStatus status)
{
    switch (status) {
    case QMediaPlayer::UnknownMediaStatus:
    case QMediaPlayer::NoMedia:
    case QMediaPlayer::LoadedMedia:
//        setStatusInfo(QString());
         qDebug() << "on_playerstatusChanged loadmedia";
        break;
    case QMediaPlayer::LoadingMedia:
        qDebug() << "on_playerstatusChanged Loading...";
        break;
    case QMediaPlayer::BufferingMedia:
    case QMediaPlayer::BufferedMedia:
//        setStatusInfo(tr("Buffering %1%").arg(m_player->bufferStatus()));
        break;
    case QMediaPlayer::StalledMedia:
//        setStatusInfo(tr("Stalled %1%").arg(m_player->bufferStatus()));
        break;
    case QMediaPlayer::EndOfMedia:
        on_btn_for_released();
        QApplication::alert(this);
        break;
    case QMediaPlayer::InvalidMedia:
//        displayErrorMessage();
        qDebug() << "on_playerstatusChanged EEROORS";
        break;
    }

}

// --------------- Queue and History Methods ---------------//


void MainWindow::on_comboBox_activated(const QString &arg1)
{
    if(arg1 == "Queue List"){
        ui->queue_tableView->setModel(m_queueListModel);
    } else {
        ui->queue_tableView->setModel(m_historyListModel);
    }
}

void MainWindow::on_actionPlay_Next_triggered()
{
    m_queueListModel->playNext(currentSlectedSongs());
}


void MainWindow::on_actionAppend_Queue_triggered()
{
    QModelIndexList selection = ui->songs_tableView->selectionModel()->selectedRows();
    QList<Model::Song> selectedSong;
    for(auto i : selection){
        m_queueListModel->appendSong(m_display_song_model->songAt(i.row()));
    }
}



//----------------------------------Playlist------------------------------------------//

void MainWindow::createNewPlaylist(){

    playlistdialog playlistdialog;
    playlistdialog.exec();

    Model::Playlist newPlaylist = playlistdialog.getPlaylist();
    qInfo() << newPlaylist.getPlaylistName();
    sppm->new_playlist(newPlaylist);

}

void MainWindow::deletePlaylist(){
    qInfo() << "gelöscht";
}

void MainWindow::addToPlaylist(){



    qInfo() << ui->songs_tableView->currentIndex().row();
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

   //ui->playlist_treeView->setModel(playlist);
}




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
            QString albumName = ui->songs_tableView->model()->index(indexrow,3).data().toString();
            qDebug() << "album : " << albumName;
                if(indexrow >= 0 && indexrow < m_display_song_model->rowCount()){
                    bool removed = sppm->deleteSong(songPath);
                    if(removed){
                        m_display_song_model->removeRow(indexrow);
                    } else {
                        ui->statusbar->showMessage("could not remove " + songName, 10000);
                    }
                    if(m_display_song_model->rowCount() <= 0){
                        // if the last song from the seeable sontable was removed
                        qDebug() << "keine songs mehr da";
//                        m_display_artist_model = new display_artist_model(sppm->allArtists(),this);
//                        ui->artists_tableView->setModel(m_display_artist_model);
                        if(m_displayState == DisplayArtists) {
                            m_display_artist_model->removeArtist(artistName);
                        } else if(m_displayState == DisplayAlbums){
                            m_display_albums_model->removeAlbum(albumName);
                        }

                    }
                }
            }
        }
}


void MainWindow::on_actionEdit_Song_triggered()
{
    Model::Song song_to_edit;
    QAbstractItemModel* selectedSong = ui->songs_tableView->model();
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
    delete selectedSong;
    EditSongDialog editDialog(song_to_edit,this);

    if(editDialog.exec() == QDialog::Accepted){
        Model::Song song_from_db = sppm->editSong(editDialog.song());
        m_display_song_model->updateSong(rowIndex,song_from_db);

        // QUESTION: Wäre ein Switchcase hierfür geeigneter?
        if(song_to_edit.getTitle() != song_from_db.getTitle())
            ui->statusbar->showMessage("Changed song title: " + song_to_edit.getTitle() + " -> " + song_from_db.getTitle(), 10000);
        if(song_to_edit.getAlbumName() != song_from_db.getAlbumName()){
            ui->statusbar->showMessage("Changed album name: " + song_to_edit.getAlbumName() + " -> " + song_from_db.getAlbumName(), 10000);
            if(m_displayState == DisplayAlbums){
                 m_display_albums_model = new Model::DisplayAlbumsModel(sppm->allAlbums(), this);
                 ui->artists_tableView->setModel(m_display_albums_model);
            }
        }
        if(song_to_edit.getAlbumNr() != song_from_db.getAlbumNr())
            ui->statusbar->showMessage("Changed song number: " + QString::number(song_to_edit.getAlbumNr()) + " -> " + song_from_db.getAlbumNr(), 10000);
        if(song_to_edit.getArtistName() != song_from_db.getArtistName()){
            ui->statusbar->showMessage("Changed artist name: " + song_to_edit.getArtistName() + " -> " + song_from_db.getArtistName(), 10000);
            if(m_displayState == DisplayArtists){
                 m_display_artist_model = new Model::DisplayArtistsModel(sppm->allArtists(), this);
                 ui->artists_tableView->setModel(m_display_artist_model);
            }
        }
    }

}


void MainWindow::on_artists_tableView_clicked(const QModelIndex &index)
{
    switch(m_displayState){
    case DisplayArtists :
        m_display_song_model = new Model::DisplaySongModel(sppm->filtered_songs_by_artist(index.data().toString()), this);
        break;
    case DisplayAlbums :
        m_display_song_model = new Model::DisplaySongModel(sppm->filtered_songs_by_album(index.data().toString()), this);
        break;
    default:
        qDebug() << "WARNING, some undefined Enum state"; // TODO:: dont have to
        break;
    }
    ui->songs_tableView->setModel(m_display_song_model);
}

void MainWindow::on_insert_search_textChanged(const QString &arg1)
{


    m_display_song_model = new Model::DisplaySongModel(sppm->search_result(arg1), this);
    ui->songs_tableView->setModel(m_display_song_model);

}
