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
