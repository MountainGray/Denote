#include "document.h"
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Graphics/page.h"


Document::Document(UI* ui){
    this->ui = ui;
}


Document::~Document(){

}


void Document::addPage(Page *page){
    pages.append(page);
    foreach(PageLayoutScene* page_layout, page_layouts){
        page_layout->addPortal(page);
        page_layout->updatePageLayout();
    }
}


void Document::removePage(Page *page){
    pages.remove(pages.indexOf(page));
    foreach(PageLayoutScene* page_layout, page_layouts){
        page_layout->removePortal(page);
    }
}


void Document::addPageLayout(PageLayoutScene *page_layout)
{
    page_layouts.append(page_layout);
}


void Document::removePageLayout(PageLayoutScene *page_layout)
{
    page_layouts.remove(page_layouts.indexOf(page_layout));
}

