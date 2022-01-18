#ifndef METADATAPLAYER_H
#define METADATAPLAYER_H
#include <QMediaPlayer>

namespace mp {

class MetaDataPlayer : public QMediaPlayer
{
public:
    MetaDataPlayer(QObject *parent);
//public slots:
//    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
};

}
#endif // METADATAPLAYER_H
