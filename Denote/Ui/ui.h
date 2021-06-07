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

public:
    void tabletPressEvent(QTabletEvent *event);
    void tabletMoveEvent(QTabletEvent *event);
    void tabletReleaseEvent(QTabletEvent *event);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    Tool *tool;
    ToolMenuViewer *tool_menu_viewer;
    Document* document;
};

#endif // UI_H
