#ifndef FILL_H
#define FILL_H

#include "Tools/tool.h"
#include <QPushButton>

class FillStroke;
class UI;

class Fill : public Tool, public QObject
{
public:
    Fill(UI* ui);

public:
    void drawPressEvent(ToolEvent event) override;
    void drawMoveEvent(ToolEvent event) override;
    void drawReleaseEvent(ToolEvent event) override;

    void activate() override{};
    void deactivate() override{};

    void paintPreset(QPaintEvent *event) override;

public:
    void setColor(QColor color);
    QColor getColor(){ return color;}

private slots:
    void updateColor();

private:
    QColor color = Qt::black;
    QPointF last_point;
    FillStroke *fill_stroke = nullptr;

private:
    QPushButton *color_button;
    QGridLayout *menu_layout;

};

#endif // FILL_H
