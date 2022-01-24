#include "metadatareader.h"

namespace MetaData {

MetaDataReader::MetaDataReader()
{
    TagLib::MPEG::File mpegFile("C:/Users/Winny/Music/Musik/Claudi Usb Stick/[1977] Lust For Life/05 - Tonight.mp3");
    TagLib::ID3v2::Tag *idv3v2tag = mpegFile.ID3v2Tag();
    qDebug()<< "title: " << idv3v2tag->title().toCString();
    qDebug()<< "genre: " << idv3v2tag->genre().toCString();
    qDebug()<< "albumNr: " << idv3v2tag->track();
    qDebug()<< "album: " << idv3v2tag->album().toCString();
    qDebug()<< "artist: " << idv3v2tag->artist().toCString();
    qDebug() << "bla blub llibtag";
}


}
