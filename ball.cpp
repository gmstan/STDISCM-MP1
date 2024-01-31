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

    checkCollision();

    dx = speed*qCos(qDegreesToRadians(angle));
    dy = speed*qSin(qDegreesToRadians(angle));

    setPos(mapToParent(dx, dy));
}

void Ball::checkCollision()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    for (QGraphicsItem* item : colliding_items) {
        Wall* wall = dynamic_cast<Wall*>(item);
        if (typeid(*item) == typeid(Wall)) {
            qDebug() << "Hit";
            qreal wallAngle = calculateWallAngle(wall);
            DoCollision(wallAngle);
            return; // Assume one collision at a time for simplicity
        }
    }
}

qreal Ball::calculateWallAngle(Wall* wall)
{
    // Retrieve the line representing the wall
    QLineF wallLine = wall->line();

    // Calculate the angle in degrees
    qreal angle = qRadiansToDegrees(qAtan2(wallLine.dy(), wallLine.dx()));

    // Calculate the angle in degrees
    //qreal angle = qRadiansToDegrees(qAtan2(wallY - ballY, wallX - ballX));

    qDebug() << angle;
    // Ensure the angle is positive and in the range [0, 360)
    angle = fmod(angle + 360.0, 360.0);

    return angle;
}

void Ball::DoCollision(qreal wallAngle)
{
    qreal reflectionAngle = 2 * wallAngle - angle;

    // Adjust the ball's angle to the new reflection angle
    angle = reflectionAngle;

    qDebug() << angle;
    // Move the ball slightly away from the wall to avoid repeated collisions
    qreal epsilon = 1.0;
    qreal reflectionX = x() + epsilon * qCos(qDegreesToRadians(reflectionAngle));
    qreal reflectionY = y() + epsilon * qSin(qDegreesToRadians(reflectionAngle));

    setPos(reflectionX, reflectionY);
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
