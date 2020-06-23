#ifndef TRACK_H
#define TRACK_H


#include <QPoint>

class QPainter;

// 敌人移动的航线
class track
{
public:
    track(QPoint pos);

    void setnext(track *nextPoint);
    track* nextWayPoint() const;
    const QPoint pos() const;

    void draw(QPainter *painter) const;

private:
    const QPoint		m_pos;
    track *			m_nextWayPoint;
};


#endif // TRACK_H
