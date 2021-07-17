#ifndef PAGEPORTAL_H
#define PAGEPORTAL_H

//QGraphicsItem displaying each page that can be moved around in a pagelayoutscene

#include <QGraphicsItem>

class Page;
class PageLayoutScene;

class PagePortal : public QGraphicsItem
{
public:
    PagePortal(Page* page, PageLayoutScene* page_layout, int index);
    ~PagePortal();

public:
    Page* getPage(){return page;}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;

private:
    Page* page;
    PageLayoutScene* page_layout;
};

#endif // PAGEPORTAL_H
