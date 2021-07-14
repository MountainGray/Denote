#include "document.h"
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Graphics/page.h"


Document::Document(UI* ui){
    this->ui = ui;
}


Document::~Document(){

}

#include <QtDebug>

void Document::addPage(Page *page, int index){
    if(index == -1 or index >= pages.length()){
        pages.append(page);
    } else {
        pages.insert(index,page);
    }

    foreach(PageLayoutScene* page_layout, page_layouts){
        page_layout->addPortal(page, index);
        page_layout->updatePageLayout();
    }
}


void Document::removePage(Page *page){
    pages.remove(pages.indexOf(page));
    foreach(PageLayoutScene* page_layout, page_layouts){
        page_layout->removePortal(page);
        page_layout->updatePageLayout();
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

