#ifndef TOOL_H
#define TOOL_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>

// todo: add all event handling void methods
class Tool
{
public:
    Tool();

public:
    virtual void tabletPressEvent(QTabletEvent *event) = 0;
    virtual void tabletMoveEvent(QTabletEvent *event) = 0;
    virtual void tabletReleaseEvent(QTabletEvent *event) = 0;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) = 0;

};

#endif // TOOL_H
