#include "toolmenuviewer.h"
#include "toolmenu.h"

ToolMenuViewer::ToolMenuViewer(QMainWindow *parent) : SubWindow(parent)
{
    setMinimumSize(200,200);
    tool_menu = new ToolMenu();
    setWidget(tool_menu);
}
