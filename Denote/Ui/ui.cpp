#include "ui.h"
#include "Tools/tool.h"
#include "Tools/pen.h"


UI::UI()
{
    tool = new Pen(this);
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






