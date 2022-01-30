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
    explicit EditSongDialog(QWidget *parent = nullptr);
    ~EditSongDialog();

private:
    Ui::EditSongDialog *ui;
};

#endif // UIEDITSONGDIALOG_H
