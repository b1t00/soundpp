#include "uiplaylistdialog.h"
#include "ui_uiplaylistdialog.h"

playlistdialog::playlistdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playlistdialog)
{
    ui->setupUi(this);
}

uiplaylistdialog::~uiplaylistdialog()
{
    delete ui;
}
