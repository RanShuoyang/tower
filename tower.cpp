#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "mainwindow.h"
#include "check_enemy.h"
#include <QPainter>
#include <QColor>
#include <QTimer>
#include <QVector2D>
#include <QtMath>
#include <QPoint>
#include "easymode.h"
#include "hardmode.h"



Tower::Tower(QPoint pos, easymode *game,int id/*=1*/)
    : m_attacking(false)
    , m_attackRange(250)
    , m_damage(10)
    , m_fireRate(1000)
    , ID(id)
    , m_chooseEnemy(nullptr)
    , m_game(game)
    , m_pos(pos)

{
    if(ID==1){
        m_sprite=QPixmap(":/1.png");
    }
    if(ID==2){
        m_sprite=QPixmap(":/3.png");
        m_damage=20;
        m_fireRate=700;
    }
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}

Tower::Tower(QPoint pos, hardmode *game,int id/*=1*/)
    : m_attacking(false)
    , m_attackRange(250)
    , m_damage(15)
    , m_fireRate(1000)
    , ID(id)
    , m_chooseEnemy(nullptr)
    , M_game(game)
    , m_pos(pos)

{
    if(ID==1){
        m_sprite=QPixmap(":/1.png");
    }
    if(ID==2){
        m_sprite=QPixmap(":/3.png");
        m_damage=30;
        m_fireRate=800;
    }
    m_fireRateTimer = new QTimer(this);
    connect(m_fireRateTimer, SIGNAL(timeout()), this, SLOT(shootWeapon()));
}
Tower::~Tower()
{
    delete m_fireRateTimer;
    m_fireRateTimer = nullptr;
}
void Tower::levelup(){
    if(m_game){
      if(ID==1){
      m_sprite=QPixmap(":/2.png");
      m_damage=25;
      }
      if(ID==2){
      m_sprite=QPixmap(":/4.png");
      m_damage=25;
      }
    }
    if(M_game){
      if(ID==1){
      m_sprite=QPixmap(":/2.png");
      m_damage=20;
      m_fireRate=1200;
      }
      if(ID==2){
      m_sprite=QPixmap(":/4.png");
      m_damage=40;
      }
    }

}
void Tower::checkEnemyInRange()
{
    if (m_chooseEnemy)
    {
        // 这种情况下,需要旋转炮台对准敌人
        // 向量标准化
        QVector2D normalized(m_chooseEnemy->pos() - m_pos);
        normalized.normalize();
        //m_rotationSprite = qRadiansToDegrees(qAtan2(normalized.y(), normalized.x())) - 90;

        // 如果敌人脱离攻击范围
        if (!collisionWithCircle(m_pos, m_attackRange, m_chooseEnemy->pos(), 1))
            lostSightOfEnemy();
    }
    else
    {
        // 遍历敌人,看是否有敌人在攻击范围内
       if(m_game){
        QList<enemy *> enemyList = m_game->enemyList();
        foreach (enemy *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
       }
       if(M_game){
        QList<enemy *> enemyList = M_game->enemyList();
        foreach (enemy *enemy, enemyList)
        {
            if (collisionWithCircle(m_pos, m_attackRange, enemy->pos(), 1))
            {
                chooseEnemyForAttack(enemy);
                break;
            }
        }
       }
    }
}

void Tower::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::white);
    painter->drawEllipse(m_pos, m_attackRange, m_attackRange);
    static const QPoint offsetPoint(-m_sprite.size().width() / 2, -m_sprite.size().height() / 2);
    painter->translate(m_pos);
    painter->drawPixmap(offsetPoint, m_sprite);
    painter->restore();
}

void Tower::attackEnemy()
{
    m_fireRateTimer->start(m_fireRate);
}

void Tower::chooseEnemyForAttack(enemy *enemy)
{
    m_chooseEnemy = enemy;
    attackEnemy();
    m_chooseEnemy->getAttacked(this);
}

void Tower::shootWeapon()
{
    QPoint p(m_pos.x()-10,m_pos.y()-60);
    if(ID==1){
        if(m_game){
            bullet *bullet = new class bullet(p, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game,1);
            bullet->move();
            m_game->addBullet(bullet);
        }
        if(M_game){
            bullet *bullet = new class bullet(p, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, M_game,1);
            bullet->move();
            M_game->addBullet(bullet);
        }
    }
    if(ID==2){
        if(m_game){
        bullet *bullet = new class bullet(p, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, m_game,2);
        bullet->move();
        m_game->addBullet(bullet);
        }
        if(M_game){
        bullet *bullet = new class bullet(p, m_chooseEnemy->pos(), m_damage, m_chooseEnemy, M_game,2);
        bullet->move();
        M_game->addBullet(bullet);
        }
    }

}

void Tower::targetKilled()
{
    if (m_chooseEnemy)
        m_chooseEnemy = nullptr;

    m_fireRateTimer->stop();

}

void Tower::lostSightOfEnemy()
{
    m_chooseEnemy->gotLostSight(this);
    if (m_chooseEnemy)
        m_chooseEnemy = nullptr;

    m_fireRateTimer->stop();

}
QPoint Tower::returnPos(){
    return m_pos;
}
