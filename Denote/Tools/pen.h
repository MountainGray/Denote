#ifndef PEN_H
#define PEN_H
#include <QColor>

#include "Tools/tool.h"
#include <QElapsedTimer>
#include <QSlider>
#include <QPushButton>
#include <QComboBox>
#include <QGridLayout>


class Stroke;
class UI;

class Pen : public Tool, public QObject
{
public:
    Pen(UI* ui);

public:
    void drawPressEvent(ToolEvent event) override;
    void drawMoveEvent(ToolEvent event) override;
    void drawReleaseEvent(ToolEvent event) override;

    void activate() override{};
    void deactivate() override{};

    void paintPreset(QPaintEvent *event) override;

public:
    void setWidth(float width);
    void setColor(QColor color);
    void setMode(QString mode){this->mode = mode;}
    float getWidth(){return width;}
    QColor getColor(){ return color;}

    float pressureToWidth(float pressure);

private slots:
    void updateWidth(int width);
    void updateColor();
    void updateMode();

private:
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
    QString mode = "Pressure";
    float dir = 0;
    float last_dir = 0;
    QPointF last_page_pos;

private:
    QSlider *width_slider;
    QPushButton *color_button;
    QComboBox *mode_combo;
    QGridLayout* menu_layout;
};

#endif // PEN_H
