#include "toolmenuviewer.h"
#include "toolmenu.h"

ToolMenuViewer::ToolMenuViewer(QMainWindow *parent) : SubWindow(parent)
{
    //setWidget(graphics);
    //docs.append(doc);

    setMinimumSize(200,200);
}

void ToolMenuViewer::setMenu(ToolMenu *menu)
{
    setWidget(menu);
}
