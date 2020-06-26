#include "choosemode.h"
#include "QPainter"
#include <QMenuBar>
#include <button.h>
#include <QTimer>
#include "easymode.h"
#include "hardmode.h"
#include "QDebug"
#include "QMediaPlayer"

choosemode::choosemode(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(1600,830);

    this->setWindowTitle("TowerDefence");

    this->setWindowIcon(QIcon(":/base.png"));

    //this->musicOn();

    QMenuBar *bar=menuBar();

    setMenuBar(bar);

    QMenu * startMenu = bar -> addMenu("开始");

    QAction * quitAction =startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
       this->close();
    });



    button * backbutton=new button(":/return.png");

    backbutton->setParent(this);

    backbutton->move(this->width()*0.5-backbutton->width()*0.5,this->height()*0.8);

    connect(backbutton,&button::clicked,[=](){

        backbutton->down();

        backbutton->up();

        QTimer::singleShot(500,this,[=](){

            emit this->chooseback();

        });
    });
    easymode *easy=new easymode;
    hardmode *hard=new hardmode;

    button *easylevel=new button(":/easy.png");

    easylevel->setParent(this);

    easylevel->move(this->width()*0.1,this->height()*0.5);

    connect(easylevel,&button::clicked,[=](){
       easylevel->down();
       easylevel->up();
       //this->musicOff();
       QTimer::singleShot(500,this,[=](){

         this->hide();

         easy->show();
       });

    });
    button *hardlevel=new button(":/hard.png");

    hardlevel->setParent(this);

    hardlevel->move(this->width()*0.75,this->height()*0.5);

    connect(hardlevel,&button::clicked,[=](){
       hardlevel->down();
       hardlevel->up();
       //this->musicOff();
       QTimer::singleShot(500,this,[=](){

         this->hide();

         hard->show();
       });

    });


}
void choosemode::paintEvent(QPaintEvent *){
    QPainter painter(this);//this 是说在主窗口画的意思
    QPixmap background(":/choose.jpg");
    painter.drawPixmap(0,0,1600,830,background);
}

