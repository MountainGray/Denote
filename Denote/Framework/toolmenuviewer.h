#ifndef TOOLMENUVIEWER_H
#define TOOLMENUVIEWER_H

<<<<<<< Updated upstream
#include "Framework/subwindow.h"

class ToolMenu;

class ToolMenuViewer : public SubWindow
{
public:
    ToolMenuViewer(QMainWindow *parent);

public:
    ToolMenu* getMenu(){return tool_menu;}
=======
#include <QStackedWidget>

class ToolMenu;

class ToolMenuViewer : public QStackedWidget
{
public:
    ToolMenuViewer();

public:
    void addToolMenu(ToolMenu* menu);
    void setToolMenu(ToolMenu* menu);
>>>>>>> Stashed changes

private:
    ToolMenu* tool_menu;

};

#endif // TOOLMENUVIEWER_H
