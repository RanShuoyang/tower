#include "enemy.h"
#include "track.h"
#include "tower.h"
#include "check_enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include "easymode.h"
#include "hardmode.h"

enemy::enemy(track *startWayPoint,easymode *game=nullptr,int id/*=1*/)
    : QObject(nullptr)
    , m_active(false)
    , ID(id)
    , m_walkingSpeed(1.5)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , m_game(game)
    , m_mode(1)

{
    if(ID==1){
        m_sprite=QPixmap(":/L1.png");
        m_maxHp=80;
        m_currentHp=80;
   }
   if(ID==2){
        m_sprite=QPixmap(":/L2.png");
        m_maxHp=200;
        m_currentHp=200;
        m_walkingSpeed=3.5;
   }
   if(ID==3){
       m_sprite=QPixmap(":/L4.png");
       m_maxHp=2500;
       m_currentHp=2500;
       m_walkingSpeed=1.2;
   }
}
enemy::enemy(track *startWayPoint,hardmode *game=nullptr,int id/*=1*/)
    : QObject(nullptr)
    , m_active(false)
    , ID(id)
    , m_walkingSpeed(1.5)
    , m_pos(startWayPoint->pos())
    , m_destinationWayPoint(startWayPoint->nextWayPoint())
    , M_game(game)
    , m_mode(2)

{
    if(ID==1){
        m_sprite=QPixmap(":/L6.png");
        m_maxHp=120;
        m_currentHp=120;
   }
   if(ID==2){
        m_sprite=QPixmap(":/L5.png");
        m_maxHp=350;
        m_currentHp=350;
        m_walkingSpeed=2.5;
   }
   if(ID==3){
       m_sprite=QPixmap(":/L4.png");
       m_maxHp=2550;
       m_currentHp=2550;
       m_walkingSpeed=1.2;
   }
   if(ID==4){
       m_sprite=QPixmap(":/L7.png");
       m_maxHp=5210;
       m_currentHp=5210;
       m_walkingSpeed=1.0;
   }
}
enemy::~enemy()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = nullptr;
    if(m_mode==1){
       m_game = nullptr;
    }
    if(m_mode==2){
       M_game = nullptr;
    }


}

void enemy::doActivate()
{
    m_active = true;
}

void enemy::move()
{
    if (!m_active)
        return;

    if (collisionWithCircle(m_pos, 1, m_destinationWayPoint->pos(), 1))
    {
        // 敌人抵达了一个航点
        if (m_destinationWayPoint->nextWayPoint())
        {
            // 还有下一个航点
            m_pos = m_destinationWayPoint->pos();
            m_destinationWayPoint = m_destinationWayPoint->nextWayPoint();
        }
        else
        {
            // 表示进入基地
            if(m_mode==1){
                m_game->getHpDamage();
                m_game->removedEnemy(this);
            }
            if(m_mode==2){
                M_game->getHpDamage();
                M_game->removedEnemy(this);
            }
            return;
        }
    }

    // 还在前往航点的路上
    // 目标航点的坐标
    QPoint targetPoint = m_destinationWayPoint->pos();
    // 未来修改这个可以添加移动状态,加快,减慢,m_walkingSpeed是基准值

    // 向量标准化
    qreal movementSpeed = m_walkingSpeed;
    QVector2D normalized(targetPoint - m_pos);
    normalized.normalize();
    m_pos = m_pos + normalized.toPoint() * movementSpeed;

    // 确定敌人选择方向

}

void enemy::draw(QPainter *painter)
{
    if (!m_active)
        return;
    static const int Health_Bar_Width = 50;
    painter->save();

    QPoint healthBarPoint ;
    if(ID==2){
        healthBarPoint= m_pos + QPoint(0,-(m_sprite.size().height()*2/3 + 10));
    }

    else if(ID==4){
        healthBarPoint= m_pos + QPoint(0,-(m_sprite.size().height()/2 + 10));
    }
    else {
       healthBarPoint= m_pos + QPoint(-m_sprite.size().width()/4,-(m_sprite.size().height()*2/3 + 10));
    }
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);


    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 5));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);

    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 5));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-m_sprite.size().width()/2, -m_sprite.size().height()*2/3);
    painter->translate(m_pos);
    // 绘制敌人
    painter->drawPixmap(offsetPoint, m_sprite);

    painter->restore();
}

void enemy::getRemoved()
{
    if (m_attackedTowersList.empty())
        return;

    foreach (Tower *attacker, m_attackedTowersList)
        attacker->targetKilled();
    // 通知game,此敌人已经阵亡
    if(m_mode==1){
        m_game->removedEnemy(this);
    }
    if(m_mode==2){
        M_game->removedEnemy(this);
    }
}

void enemy::getDamage(int damage)
{
    //m_game->audioPlayer()->playSound(LaserShootSound);
    m_currentHp -= damage;

    // 阵亡,需要移除
    if (m_currentHp <= 0)
    {

        if(m_mode==1){
          m_game->awardGold(100);
          getRemoved();
        }
        if(m_mode==2){
            M_game->awardGold(100);
            getRemoved();
        }
    }
}

void enemy::getAttacked(Tower *attacker)
{
    m_attackedTowersList.push_back(attacker);
}

// 表明敌人已经逃离了攻击范围
void enemy::gotLostSight(Tower *attacker)
{
    m_attackedTowersList.removeOne(attacker);
}

QPoint enemy::pos() const
{
    return m_pos;
}
