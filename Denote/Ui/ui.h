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
class PagePortal;
class HistoryManagerViewer;
class MainWindow;
class DocumentSummaryFrame;

class UI
{
public:
    UI(MainWindow* main_window);

public:
    void addTool(Tool* tool);
    void setActiveTool(Tool *tool);
    void setActiveDocument(Document* doc){active_document = doc;}
    void setActiveLayout(PageLayoutScene* layout){active_layout = layout;}
    void setActivePage(Page* page){active_page = page;}
    void setActivePortal(PagePortal* portal){active_portal = portal;}

    Tool* getActiveTool(){return active_tool;}
    Document* getActiveDocument(){return active_document;}
    PageLayoutScene* getActiveLayout(){return active_layout;}
    ToolMenu* getToolMenu();
    QList<Tool*> getTools(){return tools;}
    Page* getActivePage(){return active_page;}
    PagePortal* getActivePortal(){return active_portal;}
    HistoryManagerViewer* getHistoryManagerViewer(){return history_manager_viewer;}
    DocumentSummaryFrame* getSummaryFrame(){return summary_frame;}
    MainWindow* getMain(){return main_window;}

private:
    MainWindow* main_window;
    ToolMenuViewer* tool_menu_viewer;
    HistoryManagerViewer* history_manager_viewer;
    DocumentSummaryFrame* summary_frame;
    ToolLibrary* tool_library;

    QList<Tool*> tools;
    Tool* active_tool = nullptr;
    Document* active_document = nullptr;
    PageLayoutScene* active_layout = nullptr;
    Page* active_page = nullptr;
    PagePortal* active_portal = nullptr;

};

#endif // UI_H
