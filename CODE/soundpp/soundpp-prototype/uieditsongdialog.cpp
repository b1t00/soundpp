#include "uieditsongdialog.h"
#include "ui_editsongdialog.h"

EditSongDialog::EditSongDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditSongDialog)
{
    ui->setupUi(this);
}

EditSongDialog::~EditSongDialog()
{
    delete ui;
}
