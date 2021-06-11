#include "penmenu.h"
#include "Tools/pen.h"
#include <QSlider>
#include <QPushButton>
#include <QColorDialog>
#include <QGridLayout>

PenMenu::PenMenu(Pen* pen) : ToolMenu(pen)
{
    QSlider *width_slider = new QSlider(Qt::Horizontal, this);
    width_slider->setValue(2);
    width_slider->setMaximum(40);
    setPenWidth(2);
    QPushButton *button = new QPushButton("Select Color", this);

    connect(width_slider, &QSlider::valueChanged, this, &PenMenu::setPenWidth);
    connect(button, &QPushButton::clicked, this, &PenMenu::setPenColor);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(width_slider,0,0);
    layout->addWidget(button,1,0);

    this->setLayout(layout);
}


void PenMenu::setPenWidth(int width)
{
    Pen* pen = static_cast<Pen*>(tool);
    float f_width = width;
    pen->setWidth(f_width);
}


void PenMenu::setPenColor(){
    Pen* pen = static_cast<Pen*>(tool);
    QColor newColor = QColorDialog::getColor(pen->getColor());
    pen->setColor(newColor);
}
