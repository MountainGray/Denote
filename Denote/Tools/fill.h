#ifndef FILL_H
#define FILL_H

#include "Tools/tool.h"

class FillStroke;
class UI;

class Fill : public Tool
{
public:
    Fill(UI* ui);

public:
    void drawPressEvent(DrawEvent event) override;
    void drawMoveEvent(DrawEvent event) override;
    void drawReleaseEvent(DrawEvent event) override;

    void activate() override{};
    void deactivate() override{};

    void paintPreset(QPaintEvent *event) override;

public:
    void setColor(QColor color);
    QColor getColor(){ return color;}

private:
    QColor color = Qt::black;
    QPointF last_point;
    FillStroke *fill_stroke = nullptr;
};

#endif // FILL_H