#ifndef UIEDITSONGDIALOG_H
#define UIEDITSONGDIALOG_H

#include <QDialog>

namespace Ui {
class EditSongDialog;
}

class EditSongDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditSongDialog(QString m_songName,QWidget *parent = nullptr);
    ~EditSongDialog();

    QString songName() const;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::EditSongDialog *ui;

    QString m_songName;
    QString m_artistName;
    int songNr;
    QString m_albumName;
    QString m_labelName;
    QString m_labelNr;
};

#endif // UIEDITSONGDIALOG_H
