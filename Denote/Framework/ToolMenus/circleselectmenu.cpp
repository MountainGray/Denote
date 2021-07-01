#include "circleselectmenu.h"

#include "Tools/circleselect.h"
#include <QSlider>
#include <QGridLayout>


CircleSelectMenu::CircleSelectMenu(CircleSelect* select) : ToolMenu(select)
{
    this->tool = select;
    QSlider *width_slider = new QSlider(Qt::Horizontal, this);
    width_slider->setValue(2);
    width_slider->setMaximum(100);
    setEraserWidth(2);

    connect(width_slider, &QSlider::valueChanged, this, &CircleSelectMenu::setEraserWidth);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(width_slider,0,0);

    this->setLayout(layout);
}


void CircleSelectMenu::setEraserWidth(int width)
{
    float f_width = width;
    tool->setWidth(f_width);
}
