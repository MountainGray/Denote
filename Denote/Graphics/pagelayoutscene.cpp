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
}


void PageLayoutScene::updatePageLayout()
{
    QRectF bounds = QRectF();

    int i = 0;
    int x = 0;
    int y = 0;
    int max_i = portals.length();
    QTransform t = viewport->transform();
    float scale = sqrt(t.m11() * t.m11() + t.m12() * t.m12());
    int max_x = int(float(viewport->width()) / scale);
    if(max_x < 0) max_x = 0;

    int row_height = 0;

    while(true){
        portals.at(i)->setPos(x,y);
        x += portals.at(i)->getPage()->getWidth() + page_padding;
        row_height = std::max(row_height, portals.at(i)->getPage()->getHeight());
        bounds = bounds.united(portals.at(i)->sceneBoundingRect());
        i ++;
        if(i >= max_i) break;
        if(x + portals.at(i)->getPage()->getWidth() + view_padding > max_x or layout_type == SingleColumn){
            x = 0;
            y += row_height + page_padding;
            row_height = 0;
        }
    }
    setSceneRect(bounds);
}


void PageLayoutScene::addPortal(Page *page)
{
    PagePortal* portal = new PagePortal(page);
    addItem(portal);
    portals.append(portal);
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
