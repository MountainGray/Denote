#include "Tools/tool.h"
#include "Ui/ui.h"
#include "Framework/toolmenu.h"

Tool::Tool(UI* ui)
{
    this->ui = ui;
    tool_preset = new ToolPreset(this);
    tool_menu = new ToolMenu();
}
