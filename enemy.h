#ifndef ENEMY_H
#define ENEMY_H


#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>


class track;
class QPainter;
class Tower;
class easymode;
class hardmode;

class enemy : public QObject
{
    Q_OBJECT
public:
    enemy(track *startWayPoint, easymode *game,int id=1);
    enemy(track *startWayPoint, hardmode *game,int id=1);
    ~enemy();

    void draw(QPainter *painter);
    void move();
    void getDamage(int damage);
    void getRemoved();
    void getAttacked(Tower *attacker);
    void gotLostSight(Tower *attacker);

    QPoint pos() const;
public slots:
    void doActivate();


private:
    bool			m_active;
    int				m_maxHp;
    int				m_currentHp;
    int             ID;
    qreal			m_walkingSpeed;

    QPoint			m_pos;
    track *		    m_destinationWayPoint;
    easymode *	    m_game=nullptr;
    hardmode *      M_game=nullptr;
    QList<Tower *>	m_attackedTowersList;

    QPixmap   m_sprite;
};

#endif // ENEMY_H
