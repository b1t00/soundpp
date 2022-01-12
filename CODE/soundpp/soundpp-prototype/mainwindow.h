#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "soundpp.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btn_play_clicked();

    void on_btn_play_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    spp::Soundpp *spp;
};
#endif // MAINWINDOW_H
