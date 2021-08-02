#ifndef PAGE_H
#define PAGE_H

//QGraphicsScene that holds strokes on each page

#include <QGraphicsScene>

class PagePortal;

enum BackgroundType { Lines, LinesMargin, Engineering, Graph, Staves, Custom };

class Page : public QGraphicsScene
{
    Q_OBJECT
    friend PagePortal;
public:
    Page();

public:
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void setPageSize(int width, int height);
    QRectF getBounds(){ return QRectF(0,0,width,height);}
    QRectF getWorkArea(){ return work_area;}
    void setBackgroundType(BackgroundType t){ page_type = t; }
    void updatePortals(QRectF rect = QRectF());
    QList<PagePortal*> getPortals(){return portals;}
    void findLowestObject();
    void updateLowestObject(QGraphicsItem* potential_lowest);
    QGraphicsItem* getLowestObject(){return lowest_object;}
    int getLowestPoint();

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;

private:
    void paintLines(QPainter *painter);
    void paintLinesMargin(QPainter *painter);
    void paintEngineering(QPainter *painter);
    void paintGraph(QPainter *painter);
    void paintStaves(QPainter *painter);
    void paintCustom(QPainter *painter);

private:
    int width = 850;
    int height = 1100;
    BackgroundType page_type = Engineering;
    QList<PagePortal*> portals;
    QGraphicsItem* lowest_object = nullptr;
    QRectF work_area;
};

#endif // PAGE_H
