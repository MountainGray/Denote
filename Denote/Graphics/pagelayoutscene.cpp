#include "pagelayoutscene.h"
#include "Framework/document.h"
#include "pageportal.h"
#include "page.h"
#include "Graphics/documentsummaryview.h"
#include "Ui/ui.h"


PageLayoutScene::PageLayoutScene(Document *doc, DocumentView *viewport)
{
    this->doc = doc;
    this->viewport = viewport;

    doc->addLayout(this);

    int i = 0;
    foreach(Page* page, doc->getPages()){
        new PagePortal(page, this, i);
        i ++;
    }

    updatePageLayout();
}


PageLayoutScene::~PageLayoutScene()
{
    doc->removeLayout(this);

    foreach(PagePortal* portal, portals){
        delete portal;
    }

    updatePageLayout();
}


void PageLayoutScene::updatePageLayout()
{
    int padding = layout_type == Seamless ? 3 : 15;

    QRectF bounds = QRectF();
    int max_width = int(float(viewport->width()) / viewport->getScale());
    int max_i = portals.length();

    int width, height, x, y = 0, i = 0;
    QList<PagePortal*> row;

    while(i < max_i){
        width = 0;
        row.clear();
        while(i < max_i){
            if(width + portals.at(i)->getWidth() < max_width or width == 0 or layout_type == Horizontal){//if can fit, add to list
                row.append(portals.at(i));
                if(width != 0) width += padding;
                width += portals.at(i)->getWidth();
                i ++;
            } else{
                break;
            }
            if(layout_type == Vertical or layout_type == Seamless) break;
        }
        x = -width/2;
        height = 0;
        foreach(PagePortal* portal, row){
            portal->setPos(x,y);
            x += portal->getWidth();
            x += padding;
            height = std::max(height, portal->getHeight());
            bounds = bounds.united(portal->scenePageBoundingRect());
        }
        y += height;
        y += padding;
    }
    setSceneRect(bounds);
    if(focused_portal != nullptr){
        if(focused_portal->scenePageBoundingRect() != last_focused_portal_bounds){
            viewport->ensureVisible(focused_portal);
        }
        last_focused_portal_bounds = focused_portal->scenePageBoundingRect();
    }
}


void PageLayoutScene::setLayoutType(LayoutType type)
{
    layout_type = type;
    foreach(PagePortal* portal, portals){
        portal->updateRenderArea();
    }
    updatePageLayout();
}


void PageLayoutScene::setFocusedPortal(PagePortal *portal)
{
    focused_portal = portal;
    last_focused_portal_bounds = focused_portal->sceneBoundingRect();
}


void PageLayoutScene::setHoles(bool holes)
{
    this->holes = holes;
    foreach(PagePortal* portal, portals){
        portal->updateRenderArea();
    }
}


void PageLayoutScene::setShadow(bool shadow)
{
    this->shadow = shadow;
    foreach(PagePortal* portal, portals){
        portal->updateRenderArea();
    }
    updatePageLayout();
}
