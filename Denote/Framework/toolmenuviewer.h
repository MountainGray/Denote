#ifndef TOOLMENUVIEWER_H
#define TOOLMENUVIEWER_H

#include <QStackedWidget>

class ToolMenu;

class ToolMenuViewer : public QStackedWidget
{
public:
    ToolMenuViewer();

public:
    void addToolMenu(ToolMenu* menu);
    void setToolMenu(ToolMenu* menu);

private:
    ToolMenu* tool_menu;

};

#endif // TOOLMENUVIEWER_H
