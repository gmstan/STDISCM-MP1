#include "wall.h"
#include "qpen.h"

Wall::Wall(int x1, int y1, int x2, int y2, qreal width) : QGraphicsLineItem(x1, y1, x2, y2) {
    setLine(x1, y1, x2, y2);
    setPen(QPen(Qt::black, width));
}
