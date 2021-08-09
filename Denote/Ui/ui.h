#ifndef UI_H
#define UI_H

#include <QList>
#include "Framework/icolor.h"

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
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    void addTool(Tool* tool);
    void setActiveTool(Tool *tool);
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    void setActiveDocument(Document* doc){active_document = doc;}
    void setActiveLayout(PageLayoutScene* layout){active_layout = layout;}
    void setActivePage(Page* page){active_page = page;}
    void setActivePortal(PagePortal* portal){active_portal = portal;}
    void setDisplayMode(IColor::DisplayMode mode);
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
    void setWindows(DocumentSummaryFrame*, HistoryManagerViewer*, ToolMenuViewer*);
>>>>>>> Stashed changes

    Document* getActiveDocument(){return active_document;}
    PageLayoutScene* getActiveLayout(){return active_layout;}
<<<<<<< Updated upstream
    ToolMenu* getToolMenu();
    QList<Tool*> getTools(){return tools;}
=======
    void setWindows(DocumentSummaryFrame*, HistoryManagerViewer*, ToolMenuViewer*);

    Document* getActiveDocument(){return active_document;}
    PageLayoutScene* getActiveLayout(){return active_layout;}
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    Page* getActivePage(){return active_page;}
    PagePortal* getActivePortal(){return active_portal;}
    HistoryManagerViewer* getHistoryManagerViewer(){return history_manager_viewer;}
    DocumentSummaryFrame* getSummaryFrame(){return summary_frame;}
    MainWindow* getMain(){return main_window;}
    IColor::DisplayMode getDisplayMode(){return display_mode;}
<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
=======
>>>>>>> Stashed changes
    ToolMenuViewer* getToolMenuViewer(){return tool_menu_viewer;}
    Tool* getActiveTool();
    ToolLibrary* getToolLibrary(){return tool_library;}
    void setToolLibrary(ToolLibrary* library){this->tool_library = library;}
<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes

private:
    MainWindow* main_window;
    ToolMenuViewer* tool_menu_viewer;
    HistoryManagerViewer* history_manager_viewer;
    DocumentSummaryFrame* summary_frame;
    ToolLibrary* tool_library;

<<<<<<< Updated upstream
<<<<<<< Updated upstream
    QList<Tool*> tools;
    Tool* active_tool = nullptr;
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
    Document* active_document = nullptr;
    PageLayoutScene* active_layout = nullptr;
    Page* active_page = nullptr;
    PagePortal* active_portal = nullptr;
    IColor::DisplayMode display_mode = IColor::Normal;
<<<<<<< Updated upstream
<<<<<<< Updated upstream

=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
};

#endif // UI_H
