#ifndef ERASERMENU_H
#define ERASERMENU_H

#include "toolmenu.h"

class Eraser;

class EraserMenu : public ToolMenu
{
public:
    EraserMenu(Eraser* eraser);

public slots:
    void setEraserWidth(int width);

private:
    Eraser *tool;
};

#endif // ERASERMENU_H
