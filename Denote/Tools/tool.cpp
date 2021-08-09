#include "Tools/tool.h"
#include "Ui/ui.h"
#include "Framework/toolmenu.h"
<<<<<<< Updated upstream
=======
#include "Framework/toolmenuviewer.h"
>>>>>>> Stashed changes

Tool::Tool(UI* ui)
{
    this->ui = ui;
<<<<<<< Updated upstream
    tool_preset = new ToolPreset(this);
    tool_menu = new ToolMenu();
=======
    tool_library = ui->getToolLibrary();
    tool_preset = new ToolPreset(this);
    tool_menu = new ToolMenu();
    ui->getToolMenuViewer()->addToolMenu(tool_menu);
>>>>>>> Stashed changes
}
