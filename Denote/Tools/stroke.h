#ifndef STROKE_H
#define STROKE_H

#include "pressurepoint.h"
#include "Framework/undoobject.h"
#include "enums.h"

#include <QPainter>
#include <QGraphicsItem>

class Pen;

class Stroke : public QGraphicsItem, public UndoObject
{
public:
    Stroke(Pen *pen, HistoryManager* manager);
    Stroke(Stroke *stroke, HistoryManager* manager);

public:
    void init(QPointF pos, float pressure);
    void addpoint(QPointF pos, float pressure);
    void finish(QPointF pos, float pressure);

public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *ogpainter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypePenStroke;}

public:
    void undo() override;
    void redo() override;

protected:
    void updateBounds(PressurePoint point);

protected:
    QVector<PressurePoint> points;
    QPen painter_pen;
    QRectF bounds;
    QColor color;
    float width;
};

#endif // STROKE_H
