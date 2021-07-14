#include "pageportal.h"
#include "page.h"

#include <QPainter>

PagePortal::PagePortal(Page* page)
{
    this->page = page;
    page->addPortal(this);

    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
}


PagePortal::~PagePortal()
{
    page->removePortal(this);
}


void PagePortal::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    page->render(painter, page->getBounds(), page->getBounds());

    QPen pen = QPen(QColor(120,190,255),4);
    pen.setCosmetic(true);
    painter->setPen(pen);

    if(isSelected()){
        painter->drawRect(page->getBounds());
    }
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


