#ifndef UI_H
#define UI_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QKeyEvent>

class Tool;
class ToolMenu;
class ToolMenuViewer;
class ToolLibrary;
class Document;
class DocumentGraphics;


class UI
{
public:
    UI(ToolMenuViewer *tool_menu_viewer, ToolLibrary *tool_library);

public:
    void addTool(Tool* tool);
    void setActiveTool(Tool *tool);
    void setActiveDocument(Document*);
    void setActiveView(DocumentGraphics* view){active_view = view;}
    void addGraphicsView(QGraphicsView* view){graphics_views.append(view);}
    Tool* getActiveTool();
    Document* getActiveDocument();
    DocumentGraphics* getActiveView(){return active_view;}
    ToolMenu* getToolMenu();
    QList<Tool*> getTools(){return tools;}
    QList<QGraphicsView*> getGraphics(){return graphics_views;}

private:
    ToolMenuViewer *tool_menu_viewer;
    ToolLibrary *tool_library;
    QList<Tool*> tools;
    Tool *active_tool = nullptr;
    Document* active_document;
    DocumentGraphics* active_view;
    QList<QGraphicsView*> graphics_views;

};

#endif // UI_H
