#include "pagelayout.h"
#include "Framework/document.h"

PageLayout::PageLayout(Document* doc)
{
    this->doc = doc;
}


void PageLayout::updatePositions()
{
    int y = 0;
    bounds = QRectF();
    foreach(Page* page,doc->getPages()){
        page->setPos(0,y);
        y += page->getHeight();
        y += y_padding;
        bounds = bounds.united(page->sceneBoundingRect());
    }
}
