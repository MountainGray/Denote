#ifndef TOOL_H
#define TOOL_H

#include "Framework/drawevent.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>

class ToolMenu;

class Tool
{
public:
    Tool();

public:
    virtual void drawPressEvent(DrawEvent event) = 0;
    virtual void drawMoveEvent(DrawEvent event) = 0;
    virtual void drawReleaseEvent(DrawEvent event) = 0;
    virtual void drawDoubleClickEvent(DrawEvent event) = 0;

public:
    ToolMenu* toolMenu(){return tool_menu;}

protected:
    ToolMenu* tool_menu = nullptr;
};

#endif // TOOL_H
