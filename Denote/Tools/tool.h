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
    virtual void documentProximityEvent(QEvent *event){Q_UNUSED(event);}
    virtual void tabletProximityEvent(QEvent *event){Q_UNUSED(event);}
    virtual void drawPressEvent(DrawEvent event){Q_UNUSED(event);}
    virtual void drawMoveEvent(DrawEvent event){Q_UNUSED(event);}
    virtual void drawReleaseEvent(DrawEvent event){Q_UNUSED(event);}
    virtual void drawDoubleClickEvent(DrawEvent event){Q_UNUSED(event);}

    virtual void activate() = 0;
    virtual void deactivate() = 0;

public:
    ToolMenu* toolMenu(){return tool_menu;}

protected:
    ToolMenu* tool_menu = nullptr;
};

#endif // TOOL_H
