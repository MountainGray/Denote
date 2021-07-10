#ifndef PAGELAYOUT_H
#define PAGELAYOUT_H

#include "Graphics/page.h"

class Document;

class PageLayout
{
public:
    PageLayout(Document* doc);

public:
    void updatePositions();
    QRectF getBounds(){return bounds;}

private:
    Document* doc;
    QRectF bounds;

    const int y_padding = 10;
};

#endif // PAGELAYOUT_H
