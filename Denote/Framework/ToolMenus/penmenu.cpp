#include "penmenu.h"
#include "Tools/pen.h"
#include <QSlider>
#include <QPushButton>
#include <QColorDialog>
#include <QGridLayout>

PenMenu::PenMenu(Pen* pen) : ToolMenu(pen)
{
    QSlider *width_slider = new QSlider(Qt::Horizontal, this);
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
    f_width /= 10;
    pen->setWidth(f_width);
}


void PenMenu::setPenColor(){
    QColor newColor = QColorDialog::getColor();
    Pen* pen = static_cast<Pen*>(tool);
    pen->setColor(newColor);
}
