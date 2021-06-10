#ifndef TOOL_H
#define TOOL_H

#include "Framework/drawevent.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>

// todo: add all event handling void methods
class Tool
{
public:
    Tool();

public:
    virtual void drawPressEvent(DrawEvent event) = 0;
    virtual void drawMoveEvent(DrawEvent event) = 0;
    virtual void drawReleaseEvent(DrawEvent event) = 0;
    virtual void drawDoubleClickEvent(DrawEvent event) = 0;
};

#endif // TOOL_H
