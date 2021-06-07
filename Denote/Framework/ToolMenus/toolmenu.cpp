#include "toolmenu.h"
#include "Tools/tool.h"

ToolMenu::ToolMenu(Tool* tool) : QWidget()
{
    this->tool = tool;
}
