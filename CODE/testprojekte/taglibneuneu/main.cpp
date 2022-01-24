#include <QCoreApplication>
#include <QDebug>
#include "taglib/id3v1genres.h"
#include "taglib/id3v2tag.h"
#include "taglib/id3v2frame.h"
#include "taglib/id3v2header.h"
#include "taglib/mpegfile.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
//    TagLib::MPEG::File mpegFile("C:/Users/Winny/Music/Musik/Claudi Usb Stick/[1977] Lust For Life/01 - Lust For Life.mp3");
    TagLib::MPEG::File mpegFile("C:/Users/Winny/Music/Musik/Claudi Usb Stick/[1977] Lust For Life/05 - Tonight.mp3");
    TagLib::ID3v2::Tag *idv3v2tag = mpegFile.ID3v2Tag();
    qDebug()<< "title: " << idv3v2tag->title().toCString();
    qDebug()<< "genre: " << idv3v2tag->genre().toCString();
    qDebug()<< "albumNr: " << idv3v2tag->track();
    qDebug()<< "album: " << idv3v2tag->album().toCString();
    qDebug()<< "artist: " << idv3v2tag->artist().toCString();
    qDebug() << "bla blub llibtag";

    return a.exec();
}
