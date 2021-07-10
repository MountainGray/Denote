#ifndef LASSOSELECT_H
#define LASSOSELECT_H

#include "tool.h"

#include <QGraphicsItem>

class UI;
class SelectionBox;

class LassoSelect : public Tool, public QGraphicsItem, public QObject
{
public:
    LassoSelect(UI* ui, SelectionBox* box);

public:
    void documentProximityEvent(QEvent* event) override;
    void drawPressEvent(DrawEvent event) override;
    void drawMoveEvent(DrawEvent event) override;
    void drawReleaseEvent(DrawEvent event) override;
    void drawDoubleClickEvent(DrawEvent event) override;

    void activate() override;
    void deactivate() override;

    void paintPreset(QPaintEvent *event) override;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypeLassoSelect;}

private:
    QPolygonF lasso;
    bool selecting = false;
    bool added = false;
    QRectF bounds;

private:
    SelectionBox* box;
};

#endif // LASSOSELECT_H
