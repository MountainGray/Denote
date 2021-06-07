#ifndef TOOLMENU_H
#define TOOLMENU_H

#include <QWidget>

class Tool;

class ToolMenu : public QWidget
{
public:
    ToolMenu(Tool* tool);

protected:
    Tool* tool;
};

#endif // TOOLMENU_H
