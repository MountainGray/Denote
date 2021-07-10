#ifndef FILLSTROKE_H
#define FILLSTROKE_H

#include "pressurepoint.h"
#include "enums.h"

#include <QPainter>
#include <QGraphicsItem>

class Fill;

class FillStroke : public QGraphicsItem
{
public:
    FillStroke(Fill *fill);

public:
    void init(QPointF pos);
    void addpoint(QPointF pos);
    void finish(QPointF pos);

public:
    QRectF boundingRect() const override;
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
