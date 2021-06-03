#ifndef DOCUMENT_H
#define DOCUMENT_H

#include "documentview.h"

#include <QGraphicsScene>

class Page;

class Document : public QGraphicsScene{
public:
    Document();
    ~Document();

    void addPage(Page* page);
    bool removePage(int i);


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    QPixmap background;
    DocumentView* activeView;
    QList<Page*> pages;
};

#endif // DOCUMENT_H
