#include "sprite.h"
#include <QPainter>

#include <QGraphicsPolygonItem>
#include <QPolygonF>

Sprite::Sprite()
{
    // // Load sprite image
    // m_spriteImage = QPixmap("Other files/sprite.png");

    // // Check if the pixmap is null
    // if (m_spriteImage.isNull()) {
    //     qDebug() << "Failed to load sprite image!";
    // } else {
    //     qDebug() << "Sprite image loaded successfully!";
    // }


    QPolygonF polygon;
    polygon << QPointF(50, 0)
            << QPointF(85, 15)
            << QPointF(100, 50)
            << QPointF(85, 85)
            << QPointF(50, 100)
            << QPointF(15, 85)
            << QPointF(0, 50)
            << QPointF(15, 15);

}

QRectF Sprite::boundingRect() const
{
    return QRectF(0, 0, 1, 1);
}

void Sprite::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->drawPixmap(0, 0, m_spriteImage);
}

void Sprite::setPosition(const QPointF &position)
{
    setPos(position);
}
