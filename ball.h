#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QGraphicsObject>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QtMath>
#include <wall.h>

class Ball : public QGraphicsObject
{
public:
    Ball(qreal startPosX, qreal startPosY, qreal speed, qreal angle);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    // void advance(int step) override;

// signals:
//     void

public slots:
    void moveBall(int step);

protected slots:
    void checkCollision();
    qreal calculateWallAngle(Wall *wall);
    void DoCollision(const QList<QLineF>& walls);

private:
    qreal startingPosX = 0;
    qreal startingPosY = 0;
    qreal angle = 0;
    qreal speed = 0;
};

#endif // BALL_H
