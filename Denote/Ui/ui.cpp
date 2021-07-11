#include "ui.h"
#include "Tools/tool.h"
#include "Framework/toolmenuviewer.h"
#include "Framework/toolmenu.h"
#include "Framework/toollibrary.h"


UI::UI(ToolMenuViewer *tool_menu_viewer, ToolLibrary *tool_library)
{
    this->tool_menu_viewer = tool_menu_viewer;
    this->tool_library = tool_library;
}


void UI::addTool(Tool *tool)
{
    tools.append(tool);
    tool_library->addTool(tool);
    setActiveTool(tool);
}


void UI::setActiveTool(Tool *tool){
    if(active_tool != nullptr){
        active_tool->deactivate();
    }
    active_tool = tool;
    tool_library->setActiveTool(tool);
    tool_menu_viewer->setWidget(tool->getToolMenu());
    tool->activate();
}


ToolMenu *UI::getToolMenu()
{
    return tool_menu_viewer->getMenu();
}







