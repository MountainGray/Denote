#ifndef UI_H
#define UI_H

#include <QList>

class Tool;
class ToolMenu;
class ToolMenuViewer;
class ToolLibrary;
class Document;
class PageLayoutScene;
class Page;


class UI
{
public:
    UI(ToolMenuViewer *tool_menu_viewer, ToolLibrary *tool_library);

public:
    void addTool(Tool* tool);
    void setActiveTool(Tool *tool);
    void setActiveDocument(Document* doc){active_document = doc;}
    void setActiveLayout(PageLayoutScene* layout){active_layout = layout;}
    void setActivePage(Page* page){active_page = page;}

    Tool* getActiveTool(){return active_tool;}
    Document* getActiveDocument(){return active_document;}
    PageLayoutScene* getActiveLayout(){return active_layout;}
    ToolMenu* getToolMenu();
    QList<Tool*> getTools(){return tools;}
    Page* getActivePage(){return active_page;}

private:
    ToolMenuViewer *tool_menu_viewer;
    ToolLibrary *tool_library;
    QList<Tool*> tools;
    Tool *active_tool = nullptr;
    Document* active_document;
    PageLayoutScene* active_layout;
    Page* active_page;
};

#endif // UI_H
