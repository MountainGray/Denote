#include "pageportal.h"
#include "page.h"
#include "pagelayoutscene.h"

#include <QPainter>

PagePortal::PagePortal(Page* page, PageLayoutScene* page_layout, int index)
{
    this->page = page;
    this->page_layout = page_layout;

    page->portals.append(this);
    page_layout->portals.insert(index, this);

    page_layout->addItem(this);
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
}


PagePortal::~PagePortal()
{
    page->portals.removeAll(this);
    page_layout->portals.removeAll(this);
    page_layout->removeItem(this);
    if(page_layout->focused_portal == this){
        page_layout->focused_portal = nullptr;
    }
}


void PagePortal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(page_layout->getDoc()->isWorkAreaCropped() and page_layout->getViewType() == Interaction){
        page->render(painter, boundingRect(), page->getWorkArea());
    } else {
        page->render(painter, page->getBounds(), page->getBounds());
    }

    QPen pen = QPen(QColor(120,190,255),4);
    pen.setCosmetic(true);
    painter->setPen(pen);

    if(isSelected()){
        painter->drawRect(boundingRect());
    }
}


QRectF PagePortal::boundingRect() const
{
    //inefficient, should cache bounds
    if(page_layout->getDoc()->isWorkAreaCropped() and page_layout->getViewType() == Interaction){
        QRectF work_area = page->getWorkArea();
        return QRectF(0,0,work_area.width(),work_area.height());
    }
    return page->getBounds();
}


