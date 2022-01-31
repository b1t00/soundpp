#include "metadatareader.h"
#include<QFile>
#include<QString>
#include <QTime>
#include <QUrl>
#include<cstring>

//#include<>
//#include <atlstr.h>

namespace MetaData {

MetaDataFromFile::MetaDataFromFile(){
}

Model::Song MetaDataFromFile::getMetaDataFromFilePath(QString filePath)
{
    TagLib::FileRef songRef((filePath.toStdString().c_str()));

    QString songName = songRef.tag()->title().toCString();
    QString artistName = songRef.tag()->artist().toCString();
    QString albumName = songRef.tag()->album().toCString();
    int songNr = songRef.tag()->track();
    QString addedDate = (QString::number(QDateTime::currentMSecsSinceEpoch())); // Unix Epoche Time

    songName = (songName == NULL) ? QUrl(filePath).fileName() : songName;
    songNr = (songNr == NULL) ? 0 : songNr;
    artistName = (artistName == NULL) ? "unknown": artistName;
    albumName = (albumName == NULL) ? "unknown": albumName;

    Model::Song song(filePath, songName,artistName,albumName, songNr,addedDate,0);
    return song;
}

}
