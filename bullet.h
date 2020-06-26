#ifndef BULLET_H
#define BULLET_H


#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class enemy;
class easymode;
class hardmode;

class bullet : QObject
{
    Q_OBJECT
    Q_PROPERTY(QPoint m_currentPos READ currentPos WRITE setCurrentPos)

public:
    bullet(QPoint startPos, QPoint targetPoint, int damage, enemy *target,
           easymode *game, int id=1);
    bullet(QPoint startPos, QPoint targetPoint, int damage, enemy *target,
           hardmode *game, int id=1);

    void draw(QPainter *painter) const;
    void move();
    void setCurrentPos(QPoint pos);
    QPoint currentPos() const;

private slots:
    void hitTarget();

private:
    const QPoint	m_startPos;
    const QPoint	m_targetPos;
    QPixmap	        m_sprite;
    QPoint			m_currentPos;
    enemy *			m_target;
    easymode *	    m_game=nullptr;
    hardmode *      M_game=nullptr;
    int				m_damage;
    int             ID;
};
#endif // BULLET_H
