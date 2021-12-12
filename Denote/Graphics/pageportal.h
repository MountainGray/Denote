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
    int getWidth(){return render_to.width();}
    int getHeight(){return render_to.height();}
    QRectF scenePageBoundingRect();

    void updateRenderArea();
    QPointF getPageOffset(){return page_offset;}

    QRectF getRenderTo(){return render_to;}

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override {return bounds;}

private:
    Page* page;
    PageLayoutScene* page_layout;
    QRectF bounds;
    QRectF render_from;
    QRectF render_to;
    QPointF page_offset;
    static const int SHADOW = 25;
};

#endif // PAGEPORTAL_H
