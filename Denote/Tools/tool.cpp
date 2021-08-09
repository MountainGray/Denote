#include "Tools/tool.h"
#include "Ui/ui.h"
#include "Framework/toolmenu.h"
#include "Framework/toolmenuviewer.h"


Tool::Tool(UI* ui)
{
    this->ui = ui;
    tool_library = ui->getToolLibrary();
    tool_preset = new ToolPreset(this);
    tool_menu = new ToolMenu();
    ui->getToolMenuViewer()->addToolMenu(tool_menu);
}
