#ifndef CIRCLESELECTMENU_H
#define CIRCLESELECTMENU_H

#include "Framework/ToolMenus/erasermenu.h"

class CircleSelect;

class CircleSelectMenu : public ToolMenu
{
public:
    CircleSelectMenu(CircleSelect* select);

public slots:
    void setEraserWidth(int width);

private:
    CircleSelect *tool;
};

#endif // CIRCLESELECTMENU_H
