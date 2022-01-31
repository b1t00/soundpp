#ifndef UIEDITSONGDIALOG_H
#define UIEDITSONGDIALOG_H

#include <QDialog>
#include "modelsong.h"

namespace Ui {
class EditSongDialog;
}

class EditSongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSongDialog(Model::Song song,QWidget *parent = nullptr);
    ~EditSongDialog();

    Model::Song song() const;
    void setSong(const Model::Song &song);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditSongDialog *ui;
    Model::Song m_song;
};

#endif // UIEDITSONGDIALOG_H
