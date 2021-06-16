#ifndef UI_H
#define UI_H

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class Tool;
class ToolMenuViewer;
class Document;

class UI
{
public:
    UI(ToolMenuViewer *tool_menu_viewer);

public:
    void addTool(Tool* tool);
    void setActiveTool(Tool *tool);
    Tool* getActiveTool();
    Document* getDocument();
    void addDocument(Document*);

    void switchTool();

private:
    QList<Tool*> tools;
    Tool *active_tool;
    ToolMenuViewer *tool_menu_viewer;
    Document* document;
};

#endif // UI_H
