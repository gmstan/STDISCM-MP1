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
    Q_OBJECT
public:
    Ball(qreal startPosX, qreal startPosY, qreal speed, qreal angle);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    qreal startingPosX = 0;
    qreal startingPosY = 0;
    qreal angle = 0;
    qreal speed = 0;
    // void advance(int step) override;

signals:
    void finish(Ball *ball, int startingPosX,int startingPosY,qreal dx,qreal dy);

public slots:
    void moveBall(int step);

    void emitFinishSignal(qreal posX, qreal posY, qreal dx, qreal dy);
protected slots:
    void checkCollision();
    qreal calculateWallAngle(Wall *wall);
    void DoCollision(const QList<QLineF>& walls);

private:

};

#endif // BALL_H
