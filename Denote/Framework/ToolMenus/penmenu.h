#ifndef PENMENU_H
#define PENMENU_H

#include "toolmenu.h"

#include <QComboBox>

class Pen;

class PenMenu : public ToolMenu
{
public:
    PenMenu(Pen* pen);

public slots:
    void setPenWidth(int width);
    void setPenColor();
    void setWidthMode();

private:
    QComboBox *combo;
    Pen *tool;
};

#endif // PENMENU_H
