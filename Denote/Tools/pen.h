#ifndef PEN_H
#define PEN_H
#include <QColor>

#include "Tools/tool.h"

class Stroke;
class UI;

class Pen : public Tool
{
public:
    Pen(UI* ui);
    Pen(QColor color, int Width = 1);

public:
    void tabletPressEvent(QTabletEvent *event) override;
    void tabletMoveEvent(QTabletEvent *event) override;
    void tabletReleaseEvent(QTabletEvent *event) override;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

    //void keyPressEvent(QKeyEvent *event) override;
    //void wheelEvent(QGraphicsSceneWheelEvent *) override;

public:
    void setWidth(float width){this->width = width;}
    void setColor(QColor color){this->color = color;}

private:
    UI* ui;
    QColor color = Qt::black;
    QPointF lastPoint;
    Stroke *stroke = nullptr;
    float width = 0;
};

#endif // PEN_H
