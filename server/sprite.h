// Sprite.h
#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsObject>

class Sprite : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Sprite();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    // Additional methods for managing the sprite's appearance and behavior
    void setPosition(const QPointF &position);
    void setScale(qreal factor);

private:
    QPixmap m_spriteImage;
};

#endif // SPRITE_H
