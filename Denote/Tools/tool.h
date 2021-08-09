#ifndef TOOL_H
#define TOOL_H

#include "Framework/toolevent.h"
#include "Framework/toolpreset.h"
#include "Framework/pageitem.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneWheelEvent>
#include <QKeyEvent>
#include <QGridLayout>

class UI;
class ToolMenu;
class ToolPreset;

class ToolLibrary;
class ToolLibrary;

class Tool
{
public:
    Tool(UI* ui);

public:
    virtual void documentProximityEvent(QEvent *event){Q_UNUSED(event);}
    virtual void tabletProximityEvent(QEvent *event){Q_UNUSED(event);}
    virtual void drawPressEvent(ToolEvent event){Q_UNUSED(event);}
    virtual void drawMoveEvent(ToolEvent event){Q_UNUSED(event);}
    virtual void drawReleaseEvent(ToolEvent event){Q_UNUSED(event);}
    virtual void drawDoubleClickEvent(ToolEvent event){Q_UNUSED(event);}

    virtual void activate() = 0;
    virtual void deactivate() = 0;

    virtual void paintPreset(QPaintEvent *event) = 0;
    virtual void setDisplayMode(IColor::DisplayMode){};

public:
    ToolMenu* getToolMenu(){return tool_menu;}

public:
    ToolPreset* toolPreset(){return tool_preset;}
    UI* getUI(){return ui;}

protected:
    UI* ui;
    ToolMenu* tool_menu = nullptr;
    ToolPreset* tool_preset = nullptr;
    ToolLibrary* tool_library;
};

#endif // TOOL_H
