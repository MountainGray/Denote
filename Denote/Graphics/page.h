#ifndef PAGE_H
#define PAGE_H

//QGraphicsScene that holds strokes on each page

#include <QGraphicsScene>

class PagePortal;
enum BackgroundType { Lines, LinesMargin, Engineering, Graph, Staves, Custom };

class Page : public QGraphicsScene
{
    Q_OBJECT
public:
    Page();

public:
    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void setPageSize(int width, int height);
    QRectF getBounds(){ return QRectF(0,0,width,height);}
    void setBackgroundType(BackgroundType t){ page_type = t; }
    void addPortal(PagePortal* page);
    void removePortal(PagePortal* page);
    void updatePortals(QRectF rect = QRectF());


protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

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

};

#endif // PAGE_H
