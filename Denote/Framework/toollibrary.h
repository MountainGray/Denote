#ifndef TOOLLIBRARY_H
#define TOOLLIBRARY_H

#include "subwindow.h"

#include <QBoxLayout>

class Tool;

class ToolLibrary : public SubWindow
{
public:
    ToolLibrary(QMainWindow *parent);

public:
    void addTool(Tool* tool);
    void setActiveTool(Tool* tool);

private:
    QWidget* library;
    QList<Tool*> presets;
    Tool* active_preset;
    QBoxLayout *layout;
};

#endif // TOOLLIBRARY_H
