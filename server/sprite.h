#ifndef SPRITE_H
#define SPRITE_H

#include <QGraphicsItem>
#include <QPixmap>
#include <QDebug>

class Sprite : public QGraphicsItem
{
public:
    explicit Sprite(int id, QGraphicsItem *parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    void setPosition(const QPointF &position);

private:
    QPixmap m_spriteImage;
    int m_id;
};

#endif // SPRITE_H
