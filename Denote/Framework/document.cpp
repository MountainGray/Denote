#include "document.h"
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Graphics/pageportal.h"
#include "Framework/History/historymanager.h"
#include "Framework/History/historymanagerviewer.h"
#include "Graphics/documentsummaryview.h"
#include "Graphics/documentsummaryframe.h"


Document::Document(UI* ui){
    this->ui = ui;

    history_manager = new HistoryManager(this);
    summary_view = new DocumentSummaryView(this);

    ui->setActiveDocument(this);
}


Document::~Document(){

}


void Document::updateAllLayouts()
{
    foreach(PageLayoutScene* page_layout, layouts){
        page_layout->updatePageLayout();
    }
    getUI()->getSummaryFrame()->getView()->getPageLayoutScene()->updatePageLayout();
}


void Document::addPage(Page *page, int index){
    if(index == -1 or index > pages.length()) index = pages.length();

    //add the page to the documents data
    pages.insert(index,page);

    //create a page_portal between the page_layout and page
    foreach(PageLayoutScene* page_layout, layouts){
        new PagePortal(page, page_layout, index);
        page_layout->updatePageLayout();
    }
}


void Document::removePage(Page *page){

    //remove the page from the documents data
    pages.removeAll(page);

    //remove the page_portal between the page_layout and page
    foreach(PagePortal* portal, page->getPortals()){
        delete portal;
    }
    updateAllLayouts();
}


void Document::movePage(Page *page, int new_index)
{
    if(new_index >= 0 and new_index < pages.length()){
        int old_index = pages.indexOf(page);
        pages.move(old_index, new_index);
        foreach(PageLayoutScene* page_layout, layouts){
            page_layout->portals.move(old_index, new_index);
            page_layout->updatePageLayout();
        }
    }
}


void Document::updateAll(QRectF update_area)
{
    foreach(Page* page, pages){
        page->updatePortals(update_area);
    }
    updateAllLayouts();
}


void Document::focusDoc()
{
    ui->setActiveDocument(this);
    ui->getHistoryManagerViewer()->setHistoryManager(history_manager);
    ui->getSummaryFrame()->setView(summary_view);
}

