#ifndef CIRCLESELECT_H
#define CIRCLESELECT_H

#include "tool.h"

#include <QGraphicsItem>
#include <QSlider>
#include <QGridLayout>

class UI;
class SelectionBox;

class CircleSelect : public Tool, public QGraphicsItem, public QObject
{
public:
    CircleSelect(UI* ui, SelectionBox* box);

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
    int type() const override {return UserType + 2;}

public:
    void setWidth(float width);
    float getWidth(){return width;}

private slots:
    void updateWidth(int width);

private:
    float width;
    bool selecting = false;
    bool visible = false;
    QRectF bounds;

private:
    QSlider *width_slider;
    QGridLayout *menu_layout;
    SelectionBox* box;
};

#endif // CIRCLESELECT_H
