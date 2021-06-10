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
    void setTool(Tool *tool);
    Tool* getTool();
    Document* getDocument();
    void addDocument(Document*);

private:
    Tool *tool;
    ToolMenuViewer *tool_menu_viewer;
    Document* document;
};

#endif // UI_H
