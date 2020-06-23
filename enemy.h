#ifndef ENEMY_H
#define ENEMY_H


#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>


class track;
class QPainter;
class MainWindow;
class Tower;

class enemy : public QObject
{
    Q_OBJECT
public:
    enemy(track *startWayPoint, MainWindow *game,int id=1);
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
    MainWindow *	m_game;
    QList<Tower *>	m_attackedTowersList;

    QPixmap   m_sprite;
};

#endif // ENEMY_H
