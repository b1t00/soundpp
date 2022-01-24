#ifndef METADATAREADER_H
#define METADATAREADER_H

#include <QDebug>
#include <QString>
#include <QUrl>
#include <QSqlQuery>


#include "taglib/id3v1genres.h"
#include "taglib/id3v2tag.h"
#include "taglib/id3v2frame.h"
#include "taglib/id3v2header.h"
#include "taglib/mpegfile.h"

#include "taglib/fileref.h"
//#include "taglib/fil"

#include "metadataitem.h"

namespace MetaData {

class MetaDataFromFile
{
public:
    MetaDataFromFile();
    MetaData::MetaDataItem getMetaDataFromFilePath(QString filePath);
};

}
#endif // METADATAREADER_H
