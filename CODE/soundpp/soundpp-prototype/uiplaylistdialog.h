#ifndef UIPLAYLISTDIALOG_H
#define UIPLAYLISTDIALOG_H

#include <QDialog>

namespace Ui {
class uiplaylistdialog;
}

class uiplaylistdialog : public QDialog
{
    Q_OBJECT

public:
    explicit uiplaylistdialog(QWidget *parent = nullptr);
    ~uiplaylistdialog();

private:
    Ui::uiplaylistdialog *ui;
};

#endif // UIPLAYLISTDIALOG_H
