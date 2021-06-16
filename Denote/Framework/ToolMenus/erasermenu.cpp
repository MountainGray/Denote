#include "erasermenu.h"

#include "Tools/eraser.h"
#include <QSlider>
#include <QGridLayout>


EraserMenu::EraserMenu(Eraser* eraser) : ToolMenu(eraser)
{
    this->tool = eraser;
    QSlider *width_slider = new QSlider(Qt::Horizontal, this);
    width_slider->setValue(2);
    width_slider->setMaximum(40);
    setEraserWidth(2);

    connect(width_slider, &QSlider::valueChanged, this, &EraserMenu::setEraserWidth);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(width_slider,0,0);

    this->setLayout(layout);
}


void EraserMenu::setEraserWidth(int width)
{
    float f_width = width;
    tool->setWidth(f_width);
}
