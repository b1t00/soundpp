#include "song.h"

namespace Model{
Song::Song()
{

}

Song::Song(QString title):

    m_title(title)
{
}


QString Song::getTitle() const
{
    return title;
}

void Song::setTitle(const QString &value)
{
    title = value;
}
}
