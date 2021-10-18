#ifndef PAGE_H
#define PAGE_H

//QGraphicsScene that holds strokes on each page

#include <QGraphicsScene>
#include "Framework/icolor.h"
#include "Framework/serializable.h"

class PagePortal;

enum BackgroundType { Lines, LinesMargin, Engineering, Graph, Staves, Blank, Custom };

class Page : public QGraphicsScene, public Serializable
{
    Q_OBJECT
    friend PagePortal;
public:
    Page();

public:
    //void update() = delete;

    void setPageSize(int width, int height);
    QRect getWorkArea(){return work_area;}
    QRect getPageBounds(){return QRect(0,0,width,height);}
    int getWidth(){return width;}
    int getHeight(){return height;}
    QSize getPageSize(){return QSize(width,height);}

    QList<PagePortal*> getPortals(){return portals;}
    void updatePortals(const QRectF &rect = QRectF());

    void findLowestObject();
    void updateLowestObject(QGraphicsItem* potential_lowest);
    QGraphicsItem* getLowestObject(){return lowest_object;}
    int getLowestPoint();

    void setBackgroundType(BackgroundType t){ page_type = t;}
    BackgroundType getBackgroundType(){return page_type;}
    void setDisplayMode(IColor::DisplayMode display_mode);

    void serializeRead(QDataStream &in) override;
    void serializeWrite(QDataStream &out) override;

    void toggleRed(){red = !red;}

    void cache();
    QPixmap getCached(){return cached;}

protected:
    void drawBackground(QPainter *painter, const QRectF &rect) override;

public://change back to private
    void paintLines(QPainter *painter);
    void paintLinesMargin(QPainter *painter);
    void paintEngineering(QPainter *painter);
    void paintGraph(QPainter *painter);
    void paintStaves(QPainter *painter);
    void paintCustom(QPainter *painter);


private:
    int width = 850;
    int height = 1100;
    QRect work_area;

    QList<PagePortal*> portals;

    IColor blue_line = IColor(QColor(43,167,255,150));
    IColor red_line = IColor(QColor(255,50,43,150));
    IColor border_green_line = IColor(QColor(56,171,87,255));
    IColor major_green_line = IColor(QColor(56,171,87,100));
    IColor minor_green_line = IColor(QColor(56,171,87,100));
    IColor alpha_black = IColor(QColor(0,0,0,125));
    IColor white_page = IColor(QColor(250,250,250));

    BackgroundType page_type = Engineering;
    QGraphicsItem* lowest_object = nullptr;

    bool red = false;

    QPixmap cached;
};

#endif // PAGE_H
