#ifndef SELECTIONBOX_H
#define SELECTIONBOX_H

#include <QGraphicsItemGroup>
#include "Tools/tool.h"

class UI;

class SelectionBox : public QGraphicsItemGroup, public Tool
{
public:
    SelectionBox(UI* ui);

public:
    void drawPressEvent(DrawEvent event) override;
    void drawMoveEvent(DrawEvent event) override;
    void drawReleaseEvent(DrawEvent event) override;

    void activate() override;
    void deactivate() override;

    void paintPreset(QPaintEvent *event) override;

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypeSelectionBox;}

private:
    QPointF first_point_diff;
    bool visible = false;
    bool moving = false;
};

#endif // SELECTIONBOX_H
