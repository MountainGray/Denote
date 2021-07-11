#include "pagelayoutscene.h"
#include "Framework/document.h"
#include "pageportal.h"
#include "page.h"


PageLayoutScene::PageLayoutScene(QGraphicsView *viewport, Document *doc)
{
    this->viewport = viewport;
    this->doc = doc;
    foreach(Page* page, doc->getPages()){
        addPortal(page);
    }
}


void PageLayoutScene::updatePageLayout()
{
    QRectF bounds = QRectF();

    int y = 0;
    int x = 0;

    foreach(PagePortal* portal, portals){
        portal->setPos(x,y);
        if(auto_layout){
            if(x == 0){
                x = portal->getPage()->getWidth() + y_padding;
            } else {
                x = 0;
                y += portal->getPage()->getHeight();
                y += y_padding;
            }
        } else {
            y += portal->getPage()->getHeight();
            y += y_padding;
        }
        bounds = bounds.united(portal->sceneBoundingRect());
    }
    setSceneRect(bounds);
}


void PageLayoutScene::addPortal(Page *page)
{
    PagePortal* portal = new PagePortal(page);
    addItem(portal);
    portals.append(portal);
    updatePageLayout();
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
    updatePageLayout();
}


void PageLayoutScene::setAutoLayout(bool b)
{
    auto_layout = b;
    updatePageLayout();
}
