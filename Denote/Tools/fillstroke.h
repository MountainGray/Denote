#ifndef FILLSTROKE_H
#define FILLSTROKE_H

#include "Framework/pageitem.h"
#include "pressurepoint.h"

#include <QPainter>

class Fill;

class FillStroke : public PageItem
{
public:
    FillStroke(Fill *fill);

public:
    void init(QPointF pos);
    void addpoint(QPointF pos);
    void finish(QPointF pos);

public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypeFillStroke;}

protected:
    void updateBounds(QPointF point);

protected:
    QVector<QPointF> points;
    QPen painter_pen;
    QBrush painter_brush;
    QRectF bounds;
    QColor color;
};

#endif // FILLSTROKE_H
