#ifndef TOOLMENUVIEWER_H
#define TOOLMENUVIEWER_H

#include "Framework/subwindow.h"

class ToolMenu;

class ToolMenuViewer : public SubWindow
{
public:
    ToolMenuViewer(QMainWindow *parent);

public:
    ToolMenu* getMenu(){return tool_menu;}

private:
    ToolMenu* tool_menu;

};

#endif // TOOLMENUVIEWER_H
