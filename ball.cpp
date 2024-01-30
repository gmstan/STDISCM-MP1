#include "ball.h"
#include "wall.h"
#include "cstdlib"
#include <QDebug>

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

    qreal angle = checkCollision();

    dx = speed*qCos(qDegreesToRadians(angle));
    dy = speed*qSin(qDegreesToRadians(angle));

    setPos(mapToParent(dx, dy));
}

qreal Ball::checkCollision()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        Wall* wall = dynamic_cast<Wall*>(item);
        if (typeid(*item) == typeid(Wall)) {
            qDebug() << "Hit";
            qreal wallAngle = calculateWallAngle(wall);
            qreal newAngle = DoCollision(wallAngle);
            return newAngle; // Assume one collision at a time for simplicity
        }
    }
}

qreal Ball::calculateWallAngle(Wall* wall)
{
    // Calculate the angle of the wall based on its position
    qreal wallX = wall->x();
    qreal wallY = wall->y();

    qDebug() << wallX;
    qDebug() << wallY;

    qreal ballX = x();
    qreal ballY = y();

    qDebug() << ballX;
    qDebug() << ballY;

    // Calculate the angle in degrees
    qreal angle = qRadiansToDegrees(qAtan2(wallY - ballY, wallX - ballX));

    qDebug() << angle;
    // Ensure the angle is positive and in the range [0, 360)
    angle = fmod(angle + 360.0, 360.0);

    return angle;
}

qreal Ball::DoCollision(qreal wallAngle)
{
    qreal reflectionAngle = 2 * wallAngle - angle;

    // Adjust the ball's angle to the new reflection angle
    angle = reflectionAngle;

    // Move the ball slightly away from the wall to avoid repeated collisions
    // qreal epsilon = 1.0;
    // setPos(mapToParent(epsilon * qCos(qDegreesToRadians(reflectionAngle)), epsilon * qSin(qDegreesToRadians(reflectionAngle))));
    return angle;
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
