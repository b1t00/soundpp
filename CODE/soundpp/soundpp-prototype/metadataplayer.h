#ifndef METADATAPLAYER_H
#define METADATAPLAYER_H
#include <QMediaPlayer>

namespace mp {

class MetaDataPlayer : QMediaPlayer
{
public:
    MetaDataPlayer();
//public slots:
//    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
};

}
#endif // METADATAPLAYER_H
