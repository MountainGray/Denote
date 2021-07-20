#include "document.h"
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Graphics/pageportal.h"


Document::Document(UI* ui){
    this->ui = ui;
    ui->setActiveDocument(this);
}


Document::~Document(){

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
    foreach(PageLayoutScene* page_layout, layouts){
        page_layout->updatePageLayout();
    }
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


void Document::updateAll()
{
    foreach(Page* page, pages){
        page->updatePortals();
    }
}

