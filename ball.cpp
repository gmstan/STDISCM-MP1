#include "ball.h"
#include<QDebug>

Ball::Ball(qreal startPosX, qreal startPosY, qreal spd, qreal direction)
{
    startingPosX = startPosX;
    startingPosY = startPosY;
    speed = spd;
    angle = direction;

    // random start position to be removed
    // startingPosX = QRandomGenerator::global()->bounded(100);
    // startingPosY = QRandomGenerator::global()->bounded(100);

}

QRectF Ball::boundingRect() const
{
    return QRect(startingPosX, startingPosY, 10, 10);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(startingPosX, startingPosY, 10, 10);

    qDebug() << scene();
    // if (
    //     painter->setBrush(Qt::green);
    // }
    // else {
    //     painter->setBrush(Qt::red);

    // }
}

void Ball::advance(int step)
{
    if (!step) return;

    qreal dx, dy;

    // if (angle == 0) {
    //     dx = speed;
    //     dy = 0;
    // } else {
        dx = speed*qCos(qDegreesToRadians(angle));
        dy = speed*qSin(qDegreesToRadians(angle));
    // }

    setPos(mapToParent(dx, dy));
}

void Ball::DoCollision()
{
    // setPos(mapToParent(dx, dy));
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
