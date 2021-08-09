#ifndef TOOLLIBRARY_H
#define TOOLLIBRARY_H

<<<<<<< Updated upstream
<<<<<<< Updated upstream
#include "subwindow.h"

#include <QBoxLayout>
=======
#include <QWidget>
#include <QVBoxLayout>
>>>>>>> Stashed changes

class Tool;
class UI;

class ToolLibrary : public QWidget
{
public:
<<<<<<< Updated upstream
    ToolLibrary(QMainWindow *parent);
=======
#include <QWidget>
#include <QVBoxLayout>

class Tool;
class UI;

class ToolLibrary : public QWidget
{
public:
    ToolLibrary(UI* ui);
>>>>>>> Stashed changes
=======
    ToolLibrary(UI* ui);
>>>>>>> Stashed changes

public:
    void addTool(Tool* tool);
    void setActiveTool(Tool* tool);

<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
    Tool* getActiveTool(){return active_tool;}
    QList<Tool*> getTools(){return tools;}

>>>>>>> Stashed changes
private:
    UI* ui;
    QWidget* library;
<<<<<<< Updated upstream
    QList<Tool*> presets;
    Tool* active_preset;
    QBoxLayout *layout;
=======
    Tool* getActiveTool(){return active_tool;}
    QList<Tool*> getTools(){return tools;}

private:
    UI* ui;
    QWidget* library;
    QList<Tool*> tools;
    Tool* active_tool;
    QVBoxLayout *layout;
>>>>>>> Stashed changes
=======
    QList<Tool*> tools;
    Tool* active_tool;
    QVBoxLayout *layout;
>>>>>>> Stashed changes
};

#endif // TOOLLIBRARY_H
