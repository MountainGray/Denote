#include "ui.h"
#include "tool.h"
#include "pen.h"


UI::UI()
{
    tool = new Pen(this);
}

void UI::changeTool(Tool *tool){
    this->tool = tool;
}

Tool* UI::getTool(){
    return this->tool;
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

Document *UI::getDocument()
{
    return this->document;
}

void UI::addDocument(Document *doc){
    this->document = doc;
}
