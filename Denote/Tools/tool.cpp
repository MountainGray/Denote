#include "Tools/tool.h"

Tool::Tool(UI* ui)
{
    this->ui = ui;
    tool_preset = new ToolPreset(this);
}
