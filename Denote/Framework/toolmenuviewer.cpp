#include "toolmenuviewer.h"
#include "toolmenu.h"

<<<<<<< Updated upstream
<<<<<<< Updated upstream
ToolMenuViewer::ToolMenuViewer(QMainWindow *parent) : SubWindow(parent)
=======
ToolMenuViewer::ToolMenuViewer()
>>>>>>> Stashed changes
{
    setMinimumSize(50,50);
    //setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
}


<<<<<<< Updated upstream
    setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
=======
ToolMenuViewer::ToolMenuViewer()
{
    setMinimumSize(50,50);
    //setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Maximum);
}


=======
>>>>>>> Stashed changes
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
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}
