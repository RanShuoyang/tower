#include "track.h"
#include <QPainter>
#include <QColor>

track::track(QPoint pos)
    : m_pos(pos)
    , m_nextWayPoint(nullptr)
{
}

void track::setnext(track *nextPoint)
{
    m_nextWayPoint = nextPoint;
}

track* track::nextWayPoint() const
{
    return m_nextWayPoint;
}

const QPoint track::pos() const
{
    return m_pos;
}

void track::draw(QPainter *painter) const
{
    painter->save();
    painter->setPen(Qt::green);
    painter->drawEllipse(m_pos, 6, 6);
    painter->drawEllipse(m_pos, 2, 2);

    if (m_nextWayPoint)
        painter->drawLine(m_pos, m_nextWayPoint->m_pos);
    painter->restore();
}
