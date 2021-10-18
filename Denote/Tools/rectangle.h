#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Graphics/pageitem.h"

class Rectangle : public PageItem
{
public:
    Rectangle(QRectF rect = QRectF());

public:
    void setRect(QRectF rect);
    void setColor(QColor color);

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypeRectangle;}

private:
    QRectF rect;
    QColor color;
};

#endif // RECTANGLE_H
