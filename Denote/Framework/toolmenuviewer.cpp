#include "toolmenuviewer.h"
#include "toolmenu.h"


ToolMenuViewer::ToolMenuViewer()
{
    setMinimumSize(50,50);
    //setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
}


void ToolMenuViewer::addToolMenu(ToolMenu* menu)
{
    addWidget(menu);
    setToolMenu(menu);
}


void ToolMenuViewer::setToolMenu(ToolMenu *menu)
{
    if(indexOf(menu) == -1){
        addToolMenu(menu);
    } else {
        setCurrentWidget(menu);
        tool_menu = menu;
    }
}
