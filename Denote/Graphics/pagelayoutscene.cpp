#include "pagelayoutscene.h"
#include "Framework/document.h"
#include "pageportal.h"
#include "page.h"
#include "Graphics/documentsummaryview.h"


PageLayoutScene::PageLayoutScene(QGraphicsView *viewport, Document *doc)
{
    this->viewport = viewport;
    this->doc = doc;
    doc->addPageLayout(this);
    foreach(Page* page, doc->getPages()){
        addPortal(page);
    }
    updatePageLayout();
}


void PageLayoutScene::updatePageLayout()
{
    QRectF bounds = QRectF();
    QTransform t = viewport->transform();
    float scale = sqrt(t.m11() * t.m11() + t.m12() * t.m12());
    int max_width = int(float(viewport->width()) / scale);
    int max_i = portals.length();

    int width, height, x, y = 0, i = 0;
    QList<PagePortal*> row;

    while(i < max_i){
        width = 0;
        row.clear();
        while(i < max_i){
            if(width + portals.at(i)->getPage()->getWidth() < max_width or width == 0){//if can fit, add to list
                row.append(portals.at(i));
                if(width != 0) width += page_padding;
                width += portals.at(i)->getPage()->getWidth();
                i ++;
            } else {
                break;
            }
            if(layout_type == SingleColumn) break;
        }
        x = -width/2;
        height = 0;
        foreach(PagePortal* portal, row){
            portal->setPos(x,y);
            x += portal->getPage()->getWidth();
            x += page_padding;
            height = std::max(height, portal->getPage()->getHeight());
            bounds = bounds.united(portal->sceneBoundingRect());
        }
        y += height;
        y += page_padding;
    }
    setSceneRect(bounds);
}


void PageLayoutScene::addPortal(Page *page, int index)
{
    PagePortal* portal = new PagePortal(page);
    addItem(portal);

    if(index == -1 or index >= portals.length()){
        portals.append(portal);
    } else {
        portals.insert(index,portal);
    }
}


void PageLayoutScene::removePortal(Page *page)
{
    foreach(PagePortal* portal, portals){
        if(portal->getPage() == page){
            removeItem(portal);
            portals.remove(portals.indexOf(portal));
            delete portal;
        }
    }
}


void PageLayoutScene::movePortal(int old_index, int new_index)
{
    if(new_index >= 0 and new_index < portals.length()){
        portals.move(old_index, new_index);
    }
}
