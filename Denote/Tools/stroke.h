#ifndef STROKE_H
#define STROKE_H

#include "pressurepoint.h"

#include <QPainter>
#include <QGraphicsItem>

class Pen;

class Stroke : public QGraphicsItem
{
public:
    Stroke(Pen *pen, QColor color);

public:
    void init(QPointF pos, float pressure);
    void addpoint(QPointF pos, float pressure);
    void finish(QPointF pos, float pressure);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void updateBounds(PressurePoint point);

protected:
    QVector<PressurePoint> points;
    QRectF bounds;
    Pen* pen;
    QColor color;
};

#endif // STROKE_H
