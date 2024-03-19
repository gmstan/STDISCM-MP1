#include "sprite.h"
#include <QPainter>

Sprite::Sprite(int id, QGraphicsItem *parent)
    : QGraphicsItem(parent), m_id(id)
{
    // Load sprite image based on id
    QString imagePath;
    switch (id) {
    case 1:
        imagePath = ":/images/player1.png";
        break;
    case 2:
        imagePath = ":/images/player2.png";
        break;
    case 3:
        imagePath = ":/images/player3.png";
        break;
    // Add more cases for different sprite images
    default:
        qDebug() << "Invalid sprite id, using default sprite";
        imagePath = ":/images/player1.png";
        break;
    }

    m_spriteImage = QPixmap(imagePath);

    // Check if the pixmap is null
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
