#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "track.h"
#include "enemy.h"
#include "bullet.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include <QtDebug>
#include <easymode.h>
#include <button.h>
#include <QDebug>
#include <choosemode.h>
#include <QSound>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <introduce.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    this->setWindowTitle("TowerDefence");
    this->setWindowIcon(QIcon(":/base.png"));

    choose=new choosemode;//选择模式




    QMediaPlayer *gamesound = new QMediaPlayer;
    QMediaPlaylist * playlist=new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/Mark's Theme.mp3"));
    playlist->setCurrentIndex(1);
    playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    gamesound->setPlaylist(playlist);
    gamesound->setVolume(50);
    gamesound->play();

    introduce * intro= new introduce;
    //开始按钮
    button *startbutton = new button(":/startpress.png");
    startbutton->setParent(this);
    startbutton->move(this->width()*0.5-startbutton->width()*0.5,this->height()*0.5);
    connect(startbutton,&button::clicked,[=](){
       startbutton->down();
       startbutton->up();
       gamesound->stop();
       //延时进入
       QTimer::singleShot(500,this,[=](){
         this->hide();
         intro->show();
       });
    });




}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)//每次打开mainwindow的时候都会运行这个函数
{
    QPainter painter(this);//this 是说在主窗口画的意思
    QPixmap background(":/start.png");
    painter.drawPixmap(0,0,1600,830,background);

}




