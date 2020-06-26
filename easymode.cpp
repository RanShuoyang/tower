#include "easymode.h"
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
#include "choosemode.h"
#include <button.h>
#include "end.h"
#include "QMediaPlayer"


//static const int TowerCost = 300;

easymode::easymode(QWidget *parent)
    : QMainWindow(parent)
    , m_waves(0)
    , m_playerHp(5)
    , m_playrGold(800)
    , Tower_ID(1)
    , m_gameEnded(false)
    , m_gameWin(false)
{

    this->setWindowTitle("TowerDefence");
    this->setWindowIcon(QIcon(":/base.png"));
    this->setFixedSize(1600,830);
    loadTowerPositions();
    addWayPoints();

    QMediaPlayer *gamesound = new QMediaPlayer;

    gamesound->setMedia(QUrl("qrc:/Jump.mp3"));

    gamesound->setVolume(50);



    button *startbutton = new button(":/play.png");
    startbutton->setParent(this);
    startbutton->move(this->width()*0.5,this->height()*0.02);
    connect(startbutton,&button::clicked,[=](){
       startbutton->down();
       startbutton->up();
       gamesound->play();
       this->gameStart();
    });

    button *tower1 = new button(":/1.png");
    tower1->setParent(this);
    tower1->move(this->width()*0.55,this->height()*0.75);
    connect(tower1,&button::clicked,[=](){
       tower1->down();
       tower1->up();
       this->Tower_ID=1;
    });

    button *tower2 = new button(":/3.png");
    tower2->setParent(this);
    tower2->move(this->width()*0.65,this->height()*0.75);
    connect(tower2,&button::clicked,[=](){
       tower2->down();
       tower2->up();
       this->Tower_ID=2;
    });

    //gameStart();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));
    timer->start(30);

    // 设置300ms后游戏启动
    //QTimer::singleShot(300, this, SLOT(gameStart()));
}

easymode::~easymode()
{

}

void easymode::loadTowerPositions()
{
    QPoint positions[]=
    {
        QPoint(180,580),
        QPoint(300,580),
        QPoint(420,340),
        QPoint(680,340),
        QPoint(680,450),
        QPoint(420,450),
        QPoint(970,290),
        QPoint(1150,290)
    };
    int len=sizeof(positions)/sizeof(positions[0]);
    for(int i=0;i<len;++i){
        m_towerPositionsList.push_back(positions[i]);
    }
}

void easymode::paintEvent(QPaintEvent *)
{

    QPixmap cachePix(":/background2.png");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);
    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);
    foreach (enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);
    foreach (const bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave(&cachePainter);
    drawHP(&cachePainter);
    drawPlayerGold(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0,1600,830, cachePix);
}

void easymode::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
      QPoint pressPos = event->pos();
      auto it = m_towerPositionsList.begin();
      while (it != m_towerPositionsList.end())
       {
        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {
            if(Tower_ID==1){
                m_playrGold -= 300;
            }
            if(Tower_ID==2){
                m_playrGold-= 500;
            }
            it->setHasTower();
            Tower *tower = new Tower(it->centerPos(), this,Tower_ID);
            m_towersList.push_back(tower);
            update();
            break;
        }

        ++it;
       }
     }
    if(event->button()==Qt::RightButton){
        QPoint pressPos = event->pos();
        auto it = m_towerPositionsList.begin();
        while (it != m_towerPositionsList.end())
         {
          if (it->containPoint(pressPos)&&it->hasTower())
          {
              m_playrGold=m_playrGold+100;
              it->setHasTower(false);
              for(int i=0;i<m_towersList.size();i++){
                  if(m_towersList.at(i)->returnPos()==it->centerPos()){
                      m_towersList.takeAt(i);
                  }
              }

              update();
              break;
          }

          ++it;
         }
    }
}
void easymode::mouseDoubleClickEvent(QMouseEvent *e){
    QPoint p_position=e->pos();
    auto it=m_towerPositionsList.begin();
    while (it!=m_towerPositionsList.end()) {
        if(it->containPoint(p_position)&&it->hasTower()){
            for(int i=0;i<m_towersList.size();i++){
                if(m_towersList.at(i)->returnPos()==it->centerPos()){
                    m_towersList.at(i)->levelup();
                }
            }
            m_playrGold=m_playrGold-200;
            update();
            break;
        }
         ++it;
    }
}
bool easymode::canBuyTower() const
{
    if(Tower_ID==1){
        if (m_playrGold >= 300)
            return true;
    }
    if(Tower_ID==2){
        if (m_playrGold >= 500)
            return true;
    }
    return false;
}

void easymode::drawWave(QPainter *painter)
{
    QTransform transform;
    painter->setPen(QPen(Qt::black));
    QFont font;
    font.setFamily("Microsoft YaHei");
    font.setPointSize(16);
    painter->setFont(font);
    QFontInfo info=painter->fontInfo();
    info.family();
    info.italic();
    painter->setTransform(transform);
    painter->drawText(QPoint(50,50), QString("WAVE : %1").arg(m_waves + 1));
}

void easymode::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QPoint(300,50), QString("HP : %1").arg(m_playerHp));
}

void easymode::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::yellow));
    painter->drawText(QPoint(500,50), QString("GOLD : %1").arg(m_playrGold));
}

void easymode::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        End *loseending=new End(2);
        this->hide();
        loseending->show();
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void easymode::awardGold(int gold)
{
    m_playrGold += gold;
    update();
}

void easymode::addWayPoints()
{
    track *pos1=new track(QPoint (1400,480));
    m_tracklist.push_back(pos1);

    track *pos2=new track(QPoint (850,480));
    m_tracklist.push_back(pos2);
    pos2->setnext(pos1);

    track *pos3=new track(QPoint (850,230));
    m_tracklist.push_back(pos3);
    pos3->setnext(pos2);

    track *pos4=new track(QPoint (330,230));
    m_tracklist.push_back(pos4);
    pos4->setnext(pos3);

    track *pos5=new track(QPoint (330,480));
    m_tracklist.push_back(pos5);
    pos5->setnext(pos4);

    track *pos6=new track(QPoint (50,480));
    m_tracklist.push_back(pos6);
    pos6->setnext(pos5);
}

void easymode::getHpDamage(int damage/* = 1*/)
{

    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void easymode::removedEnemy(enemy *enemy)
{
    Q_ASSERT(enemy);

    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            End *winending=new End(1);
            this->hide();
            winending->show();
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void easymode::removedBullet(bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void easymode::addBullet(bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void easymode::updateMap()
{
    foreach (enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}



bool easymode::loadWave()
{
    if(m_waves>=6){
        return false;
    }
    track *startpoint=m_tracklist.back();
    if(m_waves<2) {
        int time[]={100,3000,5000,7000,9000,12000};
        for(int i=0;i<6;++i){
          enemy *enemy=new class enemy(startpoint,this);
          m_enemyList.push_back(enemy);
          QTimer::singleShot(time[i],enemy,SLOT(doActivate()));
        }
    }
    if(m_waves==2||m_waves==3){
        int time=100;
        for(int i=0;i<5;i++){
            enemy *enemy=new class enemy(startpoint,this);
            m_enemyList.push_back(enemy);
            QTimer::singleShot(time,enemy,SLOT(doActivate()));
            time+=2000;
        }
        for(int i=5;i<8;i++){
            enemy *enemy=new class enemy(startpoint,this,2);
            m_enemyList.push_back(enemy);
            QTimer::singleShot(time,enemy,SLOT(doActivate()));
            time+=2000;
        }
    }
    if(m_waves==4){
        int time=100;
        for(int i=0;i<10;i++){
            enemy *enemy=new class enemy(startpoint,this,2);
            m_enemyList.push_back(enemy);
            QTimer::singleShot(time,enemy,SLOT(doActivate()));
            time+=2000;
        }
    }
    if(m_waves==5){
        enemy *enemy=new class enemy(startpoint,this,3);
        m_enemyList.push_back(enemy);
        QTimer::singleShot(100,enemy,SLOT(doActivate()));
    }
    return true;
}




QList<enemy *> easymode::enemyList() const
{
    return m_enemyList;
}

void easymode::gameStart()
{
    loadWave();
}

