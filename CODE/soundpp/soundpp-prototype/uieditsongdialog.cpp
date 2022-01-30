#include "uieditsongdialog.h"
#include "ui_editsongdialog.h"

EditSongDialog::EditSongDialog(QString songName,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSongDialog)
{
    ui->setupUi(this);
    ui->lineEdit_songTitle->setText(songName);
}

EditSongDialog::~EditSongDialog()
{
    delete ui;
}

void EditSongDialog::on_buttonBox_accepted()
{
    m_songName = ui->lineEdit_songTitle->text();
}

QString EditSongDialog::songName() const
{
    return m_songName;
}
