#include "toolmenuviewer.h"
#include "toolmenu.h"

<<<<<<< Updated upstream
ToolMenuViewer::ToolMenuViewer(QMainWindow *parent) : SubWindow(parent)
{
    setMinimumSize(50,50);
    tool_menu = new ToolMenu();
    setWidget(tool_menu);

    setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
=======
ToolMenuViewer::ToolMenuViewer()
{
    setMinimumSize(50,50);
    //setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
}


void ToolMenuViewer::addToolMenu(ToolMenu* menu)
{
    addWidget(menu);
    setCurrentWidget(menu);
    tool_menu = menu;
}


void ToolMenuViewer::setToolMenu(ToolMenu *menu)
{
    if(indexOf(menu) == -1){
        addWidget(menu);
    } else {
        setCurrentWidget(menu);
    }
>>>>>>> Stashed changes
}
