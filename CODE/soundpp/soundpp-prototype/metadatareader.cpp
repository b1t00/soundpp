#include "metadatareader.h"
#include<QFile>
#include<QString>
#include<cstring>

//#include<>
//#include <atlstr.h>

namespace MetaData {

MetaDataFromFile::MetaDataFromFile()
{
}

MetaData::MetaDataItem MetaDataFromFile::getMetaDataFromFilePath(QString filePath)
{
    TagLib::FileRef songRef((filePath.toStdString().c_str()));

    QString songName = songRef.tag()->title().toCString();
    int songNr = songRef.tag()->track();
    QString artistName = songRef.tag()->artist().toCString();
    QString albumName = songRef.tag()->album().toCString();

    songName = (songName == NULL) ? "unknown": songName;
    songNr = (songNr == NULL) ? 0 : songNr;
    artistName = (artistName == NULL) ? "unknown": artistName;
    albumName = (albumName == NULL) ? "unknown": albumName;

    MetaData::MetaDataItem mi(filePath, songName, songNr, artistName, albumName);
    return mi;
}

}
