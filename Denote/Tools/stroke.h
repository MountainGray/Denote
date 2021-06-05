#ifndef STROKE_H
#define STROKE_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class Pen;

class Stroke : public QGraphicsItem
{
public:
    Stroke(Pen *pen);

public:
    void init(QGraphicsSceneMouseEvent* event);
    void addpoint(QGraphicsSceneMouseEvent* event);
    void finish(QGraphicsSceneMouseEvent* event);
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    QVector<QPointF> points;
    QRectF bounds;
    Pen* pen;
    QColor color;
    int count = 0;
};

#endif // STROKE_H
