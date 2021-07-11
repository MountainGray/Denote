#include "pageportal.h"
#include "page.h"

PagePortal::PagePortal(Page* page)
{
    this->page = page;
    page->addPortal(this);
}


PagePortal::~PagePortal()
{
    page->removePortal(this);
}


void PagePortal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    page->render(painter, page->getBounds(), page->getBounds());
}


QRectF PagePortal::boundingRect() const
{
    return page->getBounds();
}

/*

if(isSelected()){
    int thickness = 8;
    painter->setPen(QPen(QColor(120,180,255),thickness,Qt::SolidLine,Qt::SquareCap,Qt::RoundJoin));
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(QRect(0,0,width,height).adjusted(-thickness/2,-thickness/2,thickness/2,thickness/2));
}
*/


