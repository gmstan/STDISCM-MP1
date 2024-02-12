// wall.h

#ifndef WALL_H
#define WALL_H

#include <QGraphicsLineItem>

class Wall : public QGraphicsLineItem
{
public:
    Wall(qreal x1, qreal y1, qreal x2, qreal y2, qreal width = 1); // Added width parameter
};

#endif // WALL_H
