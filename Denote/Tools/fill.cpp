#include "fill.h"

#include "Tools/fillstroke.h"
#include "Framework/document.h"
#include "Framework/toolmenu.h"
#include <QColorDialog>
#include <QPainter>


Fill::Fill(UI* ui) : Tool(ui)
{
    color = QColor("red");

    color_button = new QPushButton("Select Color");

    menu_layout = new QGridLayout();
    menu_layout->addWidget(color_button,0,0);

    tool_menu->setLayout(menu_layout);

    connect(color_button, &QPushButton::clicked, this, &Fill::updateColor);
}


void Fill::drawPressEvent(DrawEvent event)
{
    if(event.button() == Qt::LeftButton and fill_stroke == nullptr){
        last_point = event.position();
        fill_stroke = new FillStroke(this);
        if(event.deviceType() == QInputDevice::DeviceType::Stylus) fill_stroke->init(event.docPos());
        else fill_stroke->init(event.docPos());
        ui->getActiveDocument()->addItem(fill_stroke);
    } else {
        drawReleaseEvent(event);
    }
}


void Fill::drawMoveEvent(DrawEvent event)
{
    if(fill_stroke != nullptr){
        float dx = event.position().x()-last_point.x();
        float dy = event.position().y()-last_point.y();
        float dist = sqrt(dx*dx+dy*dy);

        if (event.deviceType() == QInputDevice::DeviceType::Mouse and dist >= 3){//min distance to add new point for mouse
            fill_stroke->addpoint(event.docPos());
            last_point = event.position();
        } else if (event.deviceType() == QInputDevice::DeviceType::Stylus and dist >= 1){//min distance to add new point for pen
            fill_stroke->addpoint(event.docPos());
            last_point = event.position();
        }
    }
}


void Fill::drawReleaseEvent(DrawEvent event)
{
    if(fill_stroke != nullptr){
        if(event.deviceType() == QInputDevice::DeviceType::Mouse){
            fill_stroke->finish(event.docPos());
        } else if(event.deviceType() == QInputDevice::DeviceType::Stylus){
            fill_stroke->finish(event.docPos());
        }
        fill_stroke = nullptr;
    }
}


void Fill::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,60,60));
    painter.setBrush(QBrush(color));
    painter.drawEllipse(QPointF(30,30),10,10);
    painter.drawText(QPointF(2,12),"Fill");
}


void Fill::setColor(QColor color)
{
    this->color = color;
    tool_preset->update();
}

void Fill::updateColor()
{
    color = QColorDialog::getColor(color);
}
