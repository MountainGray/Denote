#ifndef PEN_H
#define PEN_H
#include <QColor>

#include "Tools/tool.h"
#include <QElapsedTimer>

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

    void activate() override{};
    void deactivate() override{};

public:
    void setWidth(float width){this->width = width;}
    void setColor(QColor color){this->color = color;}
    void setMode(QString mode){this->mode = mode;}
    float getWidth(){return width;}
    QColor getColor(){ return color;}

    float pressureToWidth(float pressure);

private:
    UI* ui;
    QColor color = Qt::black;
    QPointF last_point;
    QPointF true_last_point;
    Stroke *stroke = nullptr;
    float width = 2;
    QElapsedTimer timer;
    int count = 0;
    float inverse_speed;
    float speed_width;
    float last_speed_width = 0;
    float sum_dist = 0;
    QString mode = "constant";
    float dir = 0;
    float last_dir = 0;
};

#endif // PEN_H
