#include "pageitem.h"
#include "Graphics/page.h"


PageItem::PageItem()
{

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
