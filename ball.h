#ifndef BALL_H
#define BALL_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QRandomGenerator>
#include <QtMath>

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

private:
    qreal startingPosX = 0;
    qreal startingPosY = 0;
    qreal angle = 0;
    qreal speed = 0;
    void DoCollision();
};

#endif // BALL_H
