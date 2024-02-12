// wall.cpp

#include "wall.h"
#include "qpen.h"

Wall::Wall(qreal x1, qreal y1, qreal x2, qreal y2, qreal width)
{
    setLine(x1, y1, x2, y2);
    setPen(QPen(Qt::black, width)); // Set the pen width
}
