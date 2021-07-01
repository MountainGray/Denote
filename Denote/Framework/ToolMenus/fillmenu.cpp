#include "fillmenu.h"
#include "Tools/fill.h"
#include <QPushButton>
#include <QColorDialog>
#include <QGridLayout>


FillMenu::FillMenu(Fill* fill) : ToolMenu(fill)
{
    this->tool = fill;

    QPushButton *button = new QPushButton("Select Color", this);
    connect(button, &QPushButton::clicked, this, &FillMenu::setFillColor);

    QGridLayout *layout = new QGridLayout(this);
    layout->addWidget(button,0,0);

    this->setLayout(layout);
}


void FillMenu::setFillColor(){
    QColor new_color = QColorDialog::getColor(tool->getColor());
    tool->setColor(new_color);
}
