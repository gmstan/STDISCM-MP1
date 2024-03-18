
#include "sprite.h"
#include <QPainter>

Sprite::Sprite()
{
    // // Load sprite image
    m_spriteImage = QPixmap(":/images/miniSprite.png");

    // // Check if the pixmap is null
    if (m_spriteImage.isNull()) {
        qDebug() << "Failed to load sprite image!";
    } else {
        qDebug() << "Sprite image loaded successfully!";
    }
}

QRectF Sprite::boundingRect() const
{
    return QRectF(QPointF(0, 0), m_spriteImage.size());
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

