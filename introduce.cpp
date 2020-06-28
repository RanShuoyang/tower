#include "introduce.h"
#include "QPainter"
#include "button.h"
#include "QTimer"
#include "choosemode.h"
#include "QSound"
#include "mainwindow.h"
introduce::introduce(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1600,830);

    this->setWindowTitle("TowerDefence");

    this->setWindowIcon(QIcon(":/base.png"));

    //choose= new choosemode;

    //QMediaPlayer *gamesound = new QMediaPlayer;

    //gamesound->setMedia(QUrl("qrc:/Jump.mp3"));

    //gamesound->setVolume(50);

    //gamesound->play();

    button * nextbutton=new button(":/press.png");

    choosemode * choose = new choosemode ;


    nextbutton->setParent(this);

    nextbutton->move(this->width()*0.5-nextbutton->width()*0.5,this->height()*0.8);

    connect(nextbutton,&button::clicked,[=](){
       nextbutton->down();
       nextbutton->up();
       //gamesound->stop();

       QTimer::singleShot(500,this,[=](){

         this->hide();

         choose->show();

         connect(choose,&choosemode::chooseback,this,[=](){
             choose->hide();
             this->show();
             //gamesound->play();
             });
       });

    });

}

void introduce::paintEvent(QPaintEvent *){
    QPainter painter(this);//this 是说在主窗口画的意思
    QPixmap background(":/introduce.png");
    painter.drawPixmap(0,0,1600,830,background);
}
