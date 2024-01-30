#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QtMath>
#include <wall.h>

class Ball : public QGraphicsItem
{
public:
    Ball(qreal startPosX, qreal startPosY, qreal speed, qreal angle);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;
protected slots:
    void advance(int step) override;
    qreal checkCollision();
    qreal calculateWallAngle(Wall *wall);
    qreal DoCollision(qreal angle);

private:
    qreal startingPosX = 0;
    qreal startingPosY = 0;
    qreal angle = 0;
    qreal speed = 0;
};

#endif // BALL_H
