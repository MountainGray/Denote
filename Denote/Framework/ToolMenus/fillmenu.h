#ifndef FILLMENU_H
#define FILLMENU_H

#include "toolmenu.h"

class Fill;

class FillMenu : public ToolMenu
{
public:
    FillMenu(Fill* fill);

public slots:
    void setFillColor();

private:
    Fill* tool;
};

#endif // FILLMENU_H
