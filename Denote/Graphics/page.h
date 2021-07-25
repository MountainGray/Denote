#ifndef PAGE_H
#define PAGE_H

//QGraphicsScene that holds strokes on each page

#include <QGraphicsScene>
#include "Framework/icolor.h"

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
    QSizeF getPageSize(){return QSizeF(width,height);}
    void setBackgroundType(BackgroundType t){ page_type = t; }
    void updatePortals(QRectF rect = QRectF());
    QList<PagePortal*> getPortals(){return portals;}
    void invertBrightness();


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

    IColor blue_line = IColor(43,167,255,150);
    IColor red_line = IColor(255,50,43,150);
    IColor border_green_line = IColor(56,171,87,255);
    IColor major_green_line = IColor(56,171,87,100);
    IColor minor_green_line = IColor(56,171,87,100);
    IColor alpha_black = IColor(0,0,0,125);
    IColor white_page = IColor("white");
};

#endif // PAGE_H
