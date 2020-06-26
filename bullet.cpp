#include "bullet.h"
#include "enemy.h"
#include "mainwindow.h"
#include <QPainter>
#include <QPropertyAnimation>
#include "easymode.h"
#include "hardmode.h"

bullet::bullet(QPoint startPos, QPoint targetPoint, int damage, enemy *target,
               easymode *game,int id/*=1*/)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_currentPos(startPos)
    , m_target(target)
    , m_game(game)
    , m_damage(damage)
    , ID(id)
{
    if(ID==1){
        m_sprite=QPixmap(":/bullet.png");
    }
    if(ID==2){
        m_sprite=QPixmap(":/bullet2.png");
    }
}

bullet::bullet(QPoint startPos, QPoint targetPoint, int damage, enemy *target,
               hardmode *game,int id/*=1*/)
    : m_startPos(startPos)
    , m_targetPos(targetPoint)
    , m_currentPos(startPos)
    , m_target(target)
    , M_game(game)
    , m_damage(damage)
    , ID(id)
{
    if(ID==1){
        m_sprite=QPixmap(":/bullet.png");
    }
    if(ID==2){
        m_sprite=QPixmap(":/bullet2.png");
    }
}

void bullet::draw(QPainter *painter) const
{
    painter->drawPixmap(m_currentPos, m_sprite);
}

void bullet::move()
{
    // 100毫秒内击中敌人
    static const int duration = 300;
    QPropertyAnimation *animation = new QPropertyAnimation(this, "m_currentPos");
    animation->setDuration(duration);
    animation->setStartValue(m_startPos);
    animation->setEndValue(m_targetPos);
    connect(animation, SIGNAL(finished()), this, SLOT(hitTarget()));

    animation->start();
}

void bullet::hitTarget()
{
    // 这样处理的原因是:
    // 可能多个炮弹击中敌人,而其中一个将其消灭,导致敌人delete
    // 后续炮弹再攻击到的敌人就是无效内存区域
    // 因此先判断下敌人是否还有效
    if(m_game){
        if (m_game->enemyList().indexOf(m_target) != -1)
            m_target->getDamage(m_damage);
        m_game->removedBullet(this);
    }
    if(M_game){
        if (M_game->enemyList().indexOf(m_target) != -1)
            m_target->getDamage(m_damage);
        M_game->removedBullet(this);
    }


}

void bullet::setCurrentPos(QPoint pos)
{
    m_currentPos = pos;
}

QPoint bullet::currentPos() const
{
    return m_currentPos;
}
