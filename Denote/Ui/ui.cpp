#include "ui.h"
#include "Tools/tool.h"
#include "Framework/toolmenuviewer.h"
#include "Framework/toolmenu.h"
#include "Framework/toollibrary.h"
#include "Framework/History/historymanagerviewer.h"
#include "mainwindow.h"
#include "Graphics/documentsummaryframe.h"

<<<<<<< Updated upstream
<<<<<<< Updated upstream
#include "Tools/pen.h"
#include "Tools/fill.h"
#include "Tools/eraser.h"
#include "Tools/selectionbox.h"
#include "Tools/circleselect.h"
#include "Tools/lassoselect.h"
=======
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
#include "Graphics/page.h"
#include "Framework/document.h"


UI::UI(MainWindow* main_window)
{
    this->main_window = main_window;

<<<<<<< Updated upstream
<<<<<<< Updated upstream
    tool_library = new ToolLibrary(main_window);
    summary_frame = new DocumentSummaryFrame(main_window);
    tool_menu_viewer = new ToolMenuViewer(main_window);
    history_manager_viewer = new HistoryManagerViewer(main_window);
=======
    //tool_library = new ToolLibrary(main_window);
    //summary_frame = new DocumentSummaryFrame();
    //tool_menu_viewer = new ToolMenuViewer(main_window);
    //history_manager_viewer = new HistoryManagerViewer(main_window);
>>>>>>> Stashed changes


    //main_window->addSubWindow(tool_library, Qt::TopDockWidgetArea);
    //main_window->addSubWindow(summary_frame, Qt::BottomDockWidgetArea);
    //main_window->addSubWindow(tool_menu_viewer, Qt::BottomDockWidgetArea);
    //main_window->addSubWindow(history_manager_viewer, Qt::BottomDockWidgetArea);



<<<<<<< Updated upstream
    foreach(Tool* tool, tools){
        tool->toolPreset()->update();
    }
}


ToolMenu *UI::getToolMenu()
{
    return tool_menu_viewer->getMenu();
=======
    //tool_library = new ToolLibrary(main_window);
    //summary_frame = new DocumentSummaryFrame();
    //tool_menu_viewer = new ToolMenuViewer(main_window);
    //history_manager_viewer = new HistoryManagerViewer(main_window);


    //main_window->addSubWindow(tool_library, Qt::TopDockWidgetArea);
    //main_window->addSubWindow(summary_frame, Qt::BottomDockWidgetArea);
    //main_window->addSubWindow(tool_menu_viewer, Qt::BottomDockWidgetArea);
    //main_window->addSubWindow(history_manager_viewer, Qt::BottomDockWidgetArea);



>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes
}


void UI::setDisplayMode(IColor::DisplayMode mode)
{
    foreach(Page* page, getActiveDocument()->getPages()){
        foreach(QGraphicsItem* item, page->items()){
            PageItem* page_item = static_cast<PageItem*>(item);
            if(page_item != nullptr){
                page_item->setDisplayMode(mode);
            }
        }
        page->setDisplayMode(mode);
        page->update();
        page->updatePortals();
    }
<<<<<<< Updated upstream
<<<<<<< Updated upstream
    foreach(Tool* tool, getTools()){
=======
    foreach(Tool* tool, tool_library->getTools()){
>>>>>>> Stashed changes
=======
    foreach(Tool* tool, tool_library->getTools()){
>>>>>>> Stashed changes
        tool->setDisplayMode(mode);
    }

    display_mode = mode;
}


<<<<<<< Updated upstream
<<<<<<< Updated upstream
=======
=======
>>>>>>> Stashed changes
void UI::setWindows(DocumentSummaryFrame* pages, HistoryManagerViewer* history, ToolMenuViewer* settings)
{
    summary_frame = pages;
    history_manager_viewer = history;
    tool_menu_viewer = settings;
}


Tool *UI::getActiveTool()
{
    return tool_library->getActiveTool();
}


<<<<<<< Updated upstream
>>>>>>> Stashed changes
=======
>>>>>>> Stashed changes





