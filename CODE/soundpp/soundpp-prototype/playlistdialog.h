#ifndef PLAYLISTDIALOG_H
#define PLAYLISTDIALOG_H

#include <QDialog>
#include "modelsong.h"

namespace Ui {
class playlistdialog;
}

class playlistdialog : public QDialog
{
    Q_OBJECT

public:
    explicit playlistdialog(QWidget *parent = nullptr);
    ~playlistdialog();

    void setPlaylistName(QString name);
    void setPlaylistGenre(QString genre);

    QString playlistName() const;
    QString playlistGenre() const;


private slots:
    void on_pushButton_clicked();

private:
    Ui::playlistdialog *ui;
};

#endif // PLAYLISTDIALOG_H
