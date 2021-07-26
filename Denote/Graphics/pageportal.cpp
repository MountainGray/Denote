#include "pageportal.h"
#include "page.h"
#include "pagelayoutscene.h"

#include <QPainter>
#include <QGraphicsDropShadowEffect>


PagePortal::PagePortal(Page* page, PageLayoutScene* page_layout, int index)
{
    this->page = page;
    this->page_layout = page_layout;

    page->portals.append(this);
    page_layout->portals.insert(index, this);

    page_layout->addItem(this);
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);

    /*
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(10);
    shadow->setColor(QColor(0,0,0));
    setGraphicsEffect(shadow);
    */
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


int PagePortal::getWidth()
{
    return page->getWidth()+shadow;
}


int PagePortal::getHeight()
{
    return page->getHeight()+shadow;
}


void PagePortal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    page->render(painter, page->getBounds(), page->getBounds());

    painter->setPen(QPen(QColor("black"),2*shadow));
    painter->drawLine(3*shadow,page->getHeight()+shadow,page->getWidth()+shadow,page->getHeight()+shadow);
    painter->drawLine(page->getWidth()+shadow,3*shadow,page->getWidth()+shadow,page->getHeight());

    if(isSelected()){
        QPen pen = QPen(QColor(120,190,255),4);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->drawRect(page->getBounds());
    }
}


QRectF PagePortal::boundingRect() const
{
    return page->getBounds().adjusted(0,0,10,10);
}


