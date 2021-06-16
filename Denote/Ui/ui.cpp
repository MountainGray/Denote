#include "ui.h"
#include "Tools/tool.h"
#include "Tools/pen.h"
#include "Tools/eraser.h"
#include "Framework/ToolMenus/toolmenuviewer.h"


UI::UI(ToolMenuViewer *tool_menu_viewer)
{
    this->tool_menu_viewer = tool_menu_viewer;

    addTool(new Pen(this));
    addTool(new Eraser(this));
}


void UI::addTool(Tool *tool)
{
    tools.append(tool);
    setActiveTool(tool);
}


void UI::setActiveTool(Tool *tool){
    active_tool = tool;
    tool_menu_viewer->setMenu(active_tool->toolMenu());
}


Tool* UI::getActiveTool(){
    return active_tool;
}


Document *UI::getDocument()
{
    return document;
}


void UI::addDocument(Document *doc){
    document = doc;
}


void UI::switchTool()
{
    if(active_tool == tools.first()) setActiveTool(tools.last());
    else setActiveTool(tools.first());
}






