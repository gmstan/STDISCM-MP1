#include "ball.h"
#include "wall.h"
#include "cstdlib"


Ball::Ball(qreal startPosX, qreal startPosY, qreal spd, qreal direction)
{
    startingPosX = startPosX;
    startingPosY = startPosY;
    speed = spd;
    angle = direction;
}

QRectF Ball::boundingRect() const
{
    return QRect(startingPosX, startingPosY, 10, 10);
}

void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::red);
    painter->drawEllipse(startingPosX, startingPosY, 10, 10);
}

void Ball::moveBall(int step)
{
    if (!step) return;

    qreal dx, dy;

    checkCollision();

    dx = speed*qCos(qDegreesToRadians(angle));
    dy = speed*qSin(qDegreesToRadians(angle));
    startingPosX += dx;
    startingPosY += dy;

    QMetaObject::invokeMethod(this, "emitFinishSignal", Qt::QueuedConnection, Q_ARG(qreal, startingPosX), Q_ARG(qreal, startingPosY), Q_ARG(qreal, dx), Q_ARG(qreal, dy));
}

void Ball::emitFinishSignal(qreal posX, qreal posY, qreal dx, qreal dy)
{
    emit finish(this, posX, posY, dx, dy);
}

void Ball::checkCollision()
{
    QList<QGraphicsItem*> colliding_items = collidingItems();
    QList<QLineF> colliding_walls;

    for (QGraphicsItem* item : colliding_items) {
        if (typeid(*item) == typeid(Wall)) {
            Wall* wall = dynamic_cast<Wall*>(item);
            colliding_walls.append(wall->line());
        }
    }

    if (!colliding_walls.isEmpty()) {
        DoCollision(colliding_walls);
    }
}

qreal Ball::calculateWallAngle(Wall* wall)
{
    QLineF wallLine = wall->line();

    qreal angle = qRadiansToDegrees(qAtan2(wallLine.dy(), wallLine.dx()));
    angle = fmod(angle + 360.0, 360.0);

    return angle;
}

void Ball::DoCollision(const QList<QLineF>& walls)
{
    qreal incomingAngle = angle;
    qreal totalReflectionAngle = 0.0;
    int wallCount = 0;
\
    for (const QLineF& wallLine : walls) {
        qreal wallAngle = qRadiansToDegrees(qAtan2(wallLine.dy(), wallLine.dx()));
        qreal reflectionAngle = 2 * wallAngle - incomingAngle;
        totalReflectionAngle += reflectionAngle;
        wallCount++;
    }

    qreal averageReflectionAngle = totalReflectionAngle / wallCount;

    if (wallCount == 2){
        averageReflectionAngle -= 180;
    }
    averageReflectionAngle = totalReflectionAngle / wallCount;

    angle = averageReflectionAngle;

    qreal epsilon = 1.0;
    qreal reflectionX = startingPosX + epsilon * qCos(qDegreesToRadians(averageReflectionAngle));
    qreal reflectionY = startingPosY + epsilon * qSin(qDegreesToRadians(averageReflectionAngle));

    startingPosX = reflectionX;
    startingPosY = reflectionY;
}

QPainterPath Ball::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
