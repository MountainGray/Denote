#include "toolmenuviewer.h"
#include "toolmenu.h"

ToolMenuViewer::ToolMenuViewer(QMainWindow *parent) : SubWindow(parent)
{
    setMinimumSize(50,50);
    tool_menu = new ToolMenu();
    setWidget(tool_menu);

    setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
}
