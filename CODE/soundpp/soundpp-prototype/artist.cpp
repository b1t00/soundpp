#include "artist.h"

namespace Model{
Artist::Artist()
{

}

Artist::Artist(QString name) :
    m_name(name)
{
}

QString Artist::getName() const
{
    return m_name;
}

void Artist::setName(const QString &value)
{
    m_name = value;
}
}
