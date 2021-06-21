#ifndef UI_H
#define UI_H

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

class Tool;
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
    Tool* getActiveTool();
    Document* getActiveDocument();
    DocumentGraphics* getActiveView(){return active_view;}

private:
    ToolMenuViewer *tool_menu_viewer;
    ToolLibrary *tool_library;
    QList<Tool*> tools;
    Tool *active_tool = nullptr;
    Document* active_document;
    DocumentGraphics* active_view;

};

#endif // UI_H
