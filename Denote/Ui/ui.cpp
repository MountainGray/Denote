#include "ui.h"
#include "Tools/tool.h"
#include "Tools/pen.h"
#include "Tools/eraser.h"
#include "Framework/ToolMenus/toolmenuviewer.h"


UI::UI(ToolMenuViewer *tool_menu_viewer)
{
    this->tool_menu_viewer = tool_menu_viewer;
}


void UI::addTool(Tool *tool)
{
    tools.append(tool);
    setActiveTool(tool);
}


void UI::setActiveTool(Tool *tool){
    if(active_tool != nullptr) active_tool->deactivate();
    active_tool = tool;
    tool->activate();
    tool_menu_viewer->setMenu(active_tool->toolMenu());
}


Tool* UI::getActiveTool(){
    return active_tool;
}


Document *UI::getActiveDocument()
{
    return active_document;
}


void UI::setActiveDocument(Document *doc){
    active_document = doc;
}


void UI::switchTool()
{
    if(active_tool == tools.first()) setActiveTool(tools.last());
    else setActiveTool(tools.first());
}






