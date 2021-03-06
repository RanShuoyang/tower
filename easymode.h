#ifndef EASYMODE_H
#define EASYMODE_H



#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "enemy.h"
#include "bullet.h"
#include "choosemode.h"

class track;
class AudioPlayer;

class easymode : public QMainWindow
{
    Q_OBJECT

public:
    explicit easymode(QWidget *parent = nullptr);
    ~easymode();

    void getHpDamage(int damage = 1);
    void removedEnemy(enemy *enemy);
    void removedBullet(bullet *bullet);
    void addBullet(bullet *bullet);
    void awardGold(int gold);


    QList<enemy *> enemyList() const;
signals:
   void backtochoose();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *e);
private slots:
    void updateMap();
    void gameStart();

private:
    void loadTowerPositions();
    void addWayPoints();
private slots:
    bool loadWave();
private:
    bool canBuyTower() const;
    void drawWave(QPainter *painter);
    void drawHP(QPainter *painter);
    void drawPlayerGold(QPainter *painter);
    void doGameOver();
    void preLoadWavesInfo();

private:
    int						m_waves;
    int						m_playerHp;
    int						m_playrGold;
    int                     Tower_ID;
    bool					m_gameEnded;
    bool					m_gameWin;
    QList<TowerPosition>	m_towerPositionsList;
    QList<Tower *>			m_towersList;
    QList<track *>		    m_tracklist;
    QList<enemy *>			m_enemyList;
    QList<bullet *>			m_bulletList;
};


#endif // EASYMODE_H
