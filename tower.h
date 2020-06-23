#ifndef TOWER_H
#define TOWER_H


#include <QPoint>
#include <QSize>
#include <QPixmap>
#include <QObject>

class QPainter;
class enemy;
class MainWindow;
class QTimer;

class Tower : QObject
{
    Q_OBJECT
public:
    Tower(QPoint pos, MainWindow *game,int ID=1);
    ~Tower();
    void levelup();
    void draw(QPainter *painter) const;
    void checkEnemyInRange();
    void targetKilled();
    void attackEnemy();
    void chooseEnemyForAttack(enemy *enemy);
    void removeBullet();
    void damageEnemy();
    void lostSightOfEnemy();

private slots:
    void shootWeapon();

private:
    bool			m_attacking;
    int				m_attackRange;	// 代表塔可以攻击到敌人的距离
    int				m_damage;		// 代表攻击敌人时造成的伤害
    int				m_fireRate;		// 代表再次攻击敌人的时间间隔
    int             ID;
    enemy *			m_chooseEnemy;
    MainWindow *	m_game;
    QTimer *		m_fireRateTimer;

    QPoint	m_pos;
    QPixmap	m_sprite;


};

#endif // TOWER_H
