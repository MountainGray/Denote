#ifndef PEN_H
#define PEN_H
#include <QColor>

#include "Tools/tool.h"

class Stroke;
class UI;

class Pen : public Tool
{
public:
    Pen(UI* ui);
    Pen(QColor color, int Width = 1);

public:
    void drawPressEvent(DrawEvent event) override;
    void drawMoveEvent(DrawEvent event) override;
    void drawReleaseEvent(DrawEvent event) override;
    void drawDoubleClickEvent(DrawEvent event) override;

public:
    void setWidth(float width){this->width = width;}
    void setColor(QColor color){this->color = color;}
    float getWidth(){return width;}
    QColor getColor(){ return color;}

    float pressureToWidth(float pressure);

private:
    UI* ui;
    QColor color = Qt::black;
    QPointF lastPoint;
    Stroke *stroke = nullptr;
    float width = 0;
};

#endif // PEN_H
