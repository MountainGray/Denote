#include "penmenu.h"
#include "Tools/pen.h"
#include <QSlider>

PenMenu::PenMenu(Pen* pen) : ToolMenu(pen)
{
    QSlider *width_slider = new QSlider(Qt::Horizontal, this);
    connect(width_slider, &QSlider::valueChanged, this, setPenWidth);
}

void PenMenu::setPenWidth(int width)
{

}
