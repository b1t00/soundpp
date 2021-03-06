#ifndef SOUNDPPMANAGEMENT_H
#define SOUNDPPMANAGEMENT_H

#include <QObject>
#include <QUrl>
#include <QString>

#include "databaseconnection.h"
#include "musikplayerqt.h"
#include "metadatareader.h"

#include "modeldatamanagement.h"


namespace Management {

class SoundppManagement : public QObject
{
    Q_OBJECT
private:
    Database::DataBaseConnection *dbc;
    MusikPlayer::MusikPlayerQt *mpqt;
    MetaData::MetaDataFromFile *mdr;
    Model::DataManagement *dm;

public:
    explicit SoundppManagement(QObject *parent = nullptr);
    // database get
    QList<Model::Song> get_all_songs();
    QList<Model::Playlist> get_all_playlists();
//    QSqlQueryModel get_all_artists();
    Model::Song randomSong();
    QStringList* get_allArtists();
    QList<Model::Song> create_and_get_songs();
    QList<Model::Song> filtered_songs_by_artist(QString artist);
    QList<Model::Song> filtered_songs_by_album(QString album);
    QList<Model::Song> search_result(QString search);
    void songs_for_paylist(QString playlistName, Model::Song song);

    // Model
    QList<QString> allArtists();
    QList<QString> allAlbums();

    //MetaData / database drop

    Model::Song droppedFile(QString filePath);
    bool containsSongPath(QString songPath);
    Model::Song incrementPlayCount(Model::Song song_to_increment);
    bool deleteSong(QString filePath);
    Model::Song editSong(Model::Song edited_song);
    void new_playlist(Model::Playlist new_playlist);
    bool deletePlaylist(int playlistID);

    bool isAnySongAvalaible();

    //musikplayerqt
    bool pressPlay();
    void stopPlaying();
    void playSong(QString songPath);
    void setVolume(int volume);
    void setPosition(int position);
    bool isAudioAvailable() const;
    bool isPlaying() const;
    void press_mute(bool mute);
    void addToQueue(QUrl url);

signals:
    void positionChanged(qint64 position);
    void durationChanged(qint64 duration);
    void playerstatusChanged(QMediaPlayer::MediaStatus status);
//    void songDoubleClicked(const QModelIndex &index);

};

}
#endif // SOUNDPPMANAGEMENT_H
