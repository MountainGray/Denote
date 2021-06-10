#ifndef PENMENU_H
#define PENMENU_H

#include "toolmenu.h"

class Pen;

class PenMenu : public ToolMenu
{
public:
    PenMenu(Pen* pen);

public slots:
    void setPenWidth(int width);
    void setPenColor();
};

#endif // PENMENU_H