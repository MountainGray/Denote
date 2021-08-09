#ifndef TOOLMENUVIEWER_H
#define TOOLMENUVIEWER_H

<<<<<<< Updated upstream
<<<<<<< Updated upstream
#include "Framework/subwindow.h"
=======
#include <QStackedWidget>
>>>>>>> Stashed changes

class ToolMenu;

class ToolMenuViewer : public QStackedWidget
{
public:
    ToolMenuViewer();

public:
<<<<<<< Updated upstream
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
=======
    void addToolMenu(ToolMenu* menu);
    void setToolMenu(ToolMenu* menu);
>>>>>>> Stashed changes

private:
    ToolMenu* tool_menu;

};

#endif // TOOLMENUVIEWER_H
