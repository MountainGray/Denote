#include "rectangle.h"

#include <QPainter>

Rectangle::Rectangle(QRectF rect)
{
    setRect(rect);
}


void Rectangle::setRect(QRectF rect)
{
    setPos(rect.x(),rect.y());
    this->rect = QRectF(0,0,rect.width(),rect.height());
}


void Rectangle::setColor(QColor color)
{
    this->color = color;
    this->color.setAlpha(50);
}


QRectF Rectangle::boundingRect() const
{
    return rect;
}


void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing,true);

    painter->setPen(Qt::NoPen);
    painter->setBrush(QBrush(color));
    painter->drawRect(rect);
}
