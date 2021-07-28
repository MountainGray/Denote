#ifndef DYNAMICPAGE_H
#define DYNAMICPAGE_H

#include "Graphics/page.h"

class DynamicPage: public Page
{
public:
    DynamicPage();

    void updateHeight(int height) override;
};

#endif // DYNAMICPAGE_H
