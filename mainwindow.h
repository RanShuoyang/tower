#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "choosemode.h"

namespace Ui {
class MainWindow;
}

class track;
class enemy;
class bullet;
class AudioPlayer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
    void paintEvent(QPaintEvent *);
    choosemode * choose= nullptr;

    void MusicOn();
    void MusicOff();

signals:
   //自定义的信号
    //void play_music();

private:
    Ui::MainWindow *		ui;

};

#endif // MAINWINDOW_H
