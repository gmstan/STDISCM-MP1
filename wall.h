#ifndef WALL_H
#define WALL_H

#include <QGraphicsLineItem>

class Wall : public QGraphicsLineItem
{
public:
    Wall(int x1, int y1, int x2, int y2);
};

#endif // WALL_H
