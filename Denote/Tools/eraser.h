#ifndef ERASER_H
#define ERASER_H

#include "tool.h"

#include <QGraphicsItem>

class UI;

class Eraser : public Tool, public QGraphicsItem{
public:
    Eraser(UI* ui);

public:
    void documentProximityEvent(QEvent* event) override;
    void drawPressEvent(DrawEvent event) override;
    void drawMoveEvent(DrawEvent event) override;
    void drawReleaseEvent(DrawEvent event) override;

    void activate() override;
    void deactivate() override;

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return UserType + 2;}

public:
    void setWidth(float width);
    float getWidth(){return width;}

private:
    UI* ui;
    float width;
    bool erasing = false;
    bool visible = false;
    QRectF bounds;
};

#endif // ERASER_H
