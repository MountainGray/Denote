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






