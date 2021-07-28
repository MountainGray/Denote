#include "dynamicpage.h"

DynamicPage::DynamicPage()
{

}


void DynamicPage::updateHeight(int height)
{
    setPageSize(width, height);
    updatePortals();
}
