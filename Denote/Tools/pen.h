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


    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    void tabletPress(QTabletEvent *event) override;
    void tabletMove(QTabletEvent *event) override;
    void tabletRelease(QTabletEvent *event) override;

    //void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    //void keyPressEvent(QKeyEvent *event) override;
    //void wheelEvent(QGraphicsSceneWheelEvent *) override;

private:
    UI* ui;
    QColor color = Qt::blue;
    QPointF lastPoint;
    Stroke *stroke = nullptr;
};

#endif // PEN_H
