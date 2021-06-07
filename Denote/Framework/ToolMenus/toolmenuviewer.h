#ifndef TOOLMENUVIEWER_H
#define TOOLMENUVIEWER_H

#include "Framework/subwindow.h"

class ToolMenu;

class ToolMenuViewer : public SubWindow
{
public:
    ToolMenuViewer(QMainWindow *parent);

public:
    void setMenu(ToolMenu* menu);
};

#endif // TOOLMENUVIEWER_H
