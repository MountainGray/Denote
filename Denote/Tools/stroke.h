#ifndef STROKE_H
#define STROKE_H

#include "pressurepoint.h"
#include "Framework/pageitem.h"

#include <QPainter>

class Pen;

class Stroke : public PageItem
{
public:
    Stroke(Pen *pen);
    Stroke(Stroke *stroke);

public:
    void init(QPointF pos, float pressure);
    void addpoint(QPointF pos, float pressure);
    void finish(QPointF pos, float pressure);

public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *ogpainter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypePenStroke;}

private:
    void updateBounds(PressurePoint point);

private:
    QVector<PressurePoint> points;
    QPen painter_pen;
    QRectF bounds;
    QColor color;
    float width;
};

#endif // STROKE_H
