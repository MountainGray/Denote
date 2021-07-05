#ifndef TOOL_H
#define TOOL_H

#include "Framework/drawevent.h"
#include "Framework/toolpreset.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>
#include <QGridLayout>

class UI;
class ToolMenu;
class ToolPreset;

class Tool
{
public:
    Tool(UI* ui);

public:
    virtual void documentProximityEvent(QEvent *event){Q_UNUSED(event);}
    virtual void tabletProximityEvent(QEvent *event){Q_UNUSED(event);}
    virtual void drawPressEvent(DrawEvent event){Q_UNUSED(event);}
    virtual void drawMoveEvent(DrawEvent event){Q_UNUSED(event);}
    virtual void drawReleaseEvent(DrawEvent event){Q_UNUSED(event);}
    virtual void drawDoubleClickEvent(DrawEvent event){Q_UNUSED(event);}

    virtual void activate() = 0;
    virtual void deactivate() = 0;

    virtual void paintPreset(QPaintEvent *event) = 0;

public:
    ToolMenu* getToolMenu(){return tool_menu;}

public:
    ToolPreset* toolPreset(){return tool_preset;}
    UI* getUI(){return ui;}

protected:
    UI* ui;
    ToolMenu* tool_menu = nullptr;
    ToolPreset* tool_preset = nullptr;
};

#endif // TOOL_H
