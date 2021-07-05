#ifndef PAGE_H
#define PAGE_H

#include "Graphics/pagebackground.h"

#include <QGraphicsItem>
#include <QPainter>

enum BackgroundType { Lines, LinesMargin, Engineering, Graph, Staves, Custom };

class Page : public QGraphicsItem{
public:
    Page();

    int getWidth(){ return width; }
    int getHeight(){ return height; }
    void setBackgroundType(BackgroundType t){ page_type = t; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return UserType + 3;}

private:
    void paintLines(QPainter *painter);
    void paintLinesMargin(QPainter *painter);
    void paintEngineering(QPainter *painter);
    void paintGraph(QPainter *painter);
    void paintStaves(QPainter *painter);
    void paintCustom(QPainter *painter);

private:
    int width, height = 0;
    PageBackground background;
    BackgroundType page_type = Engineering;

};

#endif // PAGE_H
