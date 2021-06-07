#include "ui.h"
#include "Tools/tool.h"
#include "Tools/pen.h"
#include "Framework/ToolMenus/toolmenuviewer.h"
#include "Framework/ToolMenus/penmenu.h"


UI::UI(ToolMenuViewer *tool_menu_viewer)
{
    this->tool_menu_viewer = tool_menu_viewer;
    tool = new Pen(this);
    PenMenu *pen_menu = new PenMenu(static_cast<Pen*>(tool));
    tool_menu_viewer->setMenu(pen_menu);
}


void UI::setTool(Tool *tool){
    this->tool = tool;
}


Tool* UI::getTool(){
    return this->tool;
}


Document *UI::getDocument()
{
    return this->document;
}


void UI::addDocument(Document *doc){
    this->document = doc;
}


void UI::tabletPressEvent(QTabletEvent *event)
{
    tool->tabletPressEvent(event);
}


void UI::tabletMoveEvent(QTabletEvent *event)
{
    tool->tabletMoveEvent(event);
}


void UI::tabletReleaseEvent(QTabletEvent *event)
{
    tool->tabletReleaseEvent(event);
}


void UI::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    tool->mouseMoveEvent(event);
}


void UI::mousePressEvent(QGraphicsSceneMouseEvent *event){
    tool->mousePressEvent(event);
}


void UI::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    tool->mouseReleaseEvent(event);
}


void UI::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    tool->mouseDoubleClickEvent(event);
}






