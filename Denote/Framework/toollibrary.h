#ifndef TOOLLIBRARY_H
#define TOOLLIBRARY_H

#include <QWidget>
#include <QVBoxLayout>

class Tool;
class UI;

class ToolLibrary : public QWidget
{
public:
    ToolLibrary(UI* ui);

public:
    void addTool(Tool* tool);
    void setActiveTool(Tool* tool);

    Tool* getActiveTool(){return active_tool;}
    QList<Tool*> getTools(){return tools;}

private:
    UI* ui;
    QWidget* library;
    QList<Tool*> tools;
    Tool* active_tool;
    QVBoxLayout *layout;
};

#endif // TOOLLIBRARY_H
