#include "pageitem.h"


PageItem::PageItem()
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
}


void PageItem::removeItem()
{
    hide();
    setEnabled(false);
    present = false;
}


void PageItem::recoverItem()
{
    show();
    setEnabled(true);
    present = true;
}
