#ifndef HIGHLIGHTER_H
#define HIGHLIGHTER_H

#include "tool.h"
#include "Tools/rectangle.h"

#include <QGraphicsItem>
#include <QPushButton>

class Highlighter : public Tool, public QGraphicsItem, public QObject
{
public:
    Highlighter(UI* ui);

public:
    void documentProximityEvent(QEvent* event) override;
    void drawPressEvent(ToolEvent event) override;
    void drawMoveEvent(ToolEvent event) override;
    void drawReleaseEvent(ToolEvent event) override;

    void activate() override;
    void deactivate() override;

    void paintPreset(QPaintEvent *event) override;


public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypeLassoSelect;}

public:
    void setWidth(float new_width);
    float getWidth(){return width;}

private slots:
    void updateWidth(int new_width);
    void updateColor();

private:
    float width;
    QColor color;
    bool visible = false;
    QRectF bounds;
    Rectangle* highlight = nullptr;
    QRectF highlight_area;
    QPointF width_point;
    bool adjusting_width = false;
    float pause_width;

private:
    QSlider *width_slider;
    QGridLayout *menu_layout;
    QPushButton *color_button;
};

#endif // HIGHLIGHTER_H
