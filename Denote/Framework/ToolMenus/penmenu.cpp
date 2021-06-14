#include "penmenu.h"
#include "Tools/pen.h"
#include <QSlider>
#include <QPushButton>
#include <QColorDialog>
#include <QGridLayout>

PenMenu::PenMenu(Pen* pen) : ToolMenu(pen)
{
    this->tool = pen;
    QSlider *width_slider = new QSlider(Qt::Horizontal, this);
    width_slider->setValue(2);
    width_slider->setMaximum(40);
    setPenWidth(2);

    QPushButton *button = new QPushButton("Select Color", this);

    combo = new QComboBox(this);
    combo->addItems({QString("Constant"),QString("Pressure"),QString("Speed"),QString("Average"),QString("Combined")});
    combo->setCurrentIndex(0);

    connect(width_slider, &QSlider::valueChanged, this, &PenMenu::setPenWidth);
    connect(button, &QPushButton::clicked, this, &PenMenu::setPenColor);
    connect(combo, &QComboBox::currentIndexChanged, this, &PenMenu::setWidthMode);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(combo,0,0);
    layout->addWidget(width_slider,1,0);
    layout->addWidget(button,2,0);

    this->setLayout(layout);
}


void PenMenu::setPenWidth(int width)
{
    float f_width = width;
    tool->setWidth(f_width);
}


void PenMenu::setPenColor(){
    QColor newColor = QColorDialog::getColor(tool->getColor());
    tool->setColor(newColor);
}


void PenMenu::setWidthMode()
{
    tool->setMode(combo->currentText());
}
