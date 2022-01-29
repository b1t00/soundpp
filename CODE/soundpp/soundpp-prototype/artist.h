#ifndef ARTIST_H
#define ARTIST_H
#include <QString>


namespace Model {
class Artist


{
public:
    Artist();
    Artist(QString name);

    QString getName() const;
    void setName(const QString &value);

private:
    QString m_name;
};
}

#endif // ARTIST_H
