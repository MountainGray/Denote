#include "pageitem.h"
#include "Graphics/page.h"


/*
Page items should never need to call update() as that scedules a repaint for all views of the page scene.
In this case, page portals use the render() function instead and the page portals should be updated instead.




*/





PageItem::PageItem()
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
}


void PageItem::removeItem()
{
    hide();
    setEnabled(false);
    present = false;
    Page* page = static_cast<Page*>(scene());
    if(page != nullptr){
        if(page->getLowestObject() == this){
            page->findLowestObject();
        }
    }
}


void PageItem::recoverItem()
{
    show();
    setEnabled(true);
    present = true;
    Page* page = static_cast<Page*>(scene());
    if(page != nullptr){
        page->updateLowestObject(this);
    }
}


void PageItem::serializeRead(QDataStream &in)
{
    in >> present;
    QPointF new_pos;
    in >> new_pos;
    setPos(new_pos);
    QTransform new_transform;
    in >> new_transform;
    setTransform(new_transform);
}


void PageItem::serializeWrite(QDataStream &out)
{
    out << present;
    out << pos();
    out << transform();
}
