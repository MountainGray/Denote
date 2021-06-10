#include "Tools/pen.h"

#include "Tools/stroke.h"
#include "Ui/ui.h"
#include "Framework/document.h"


Pen::Pen(UI* ui)
{
    this->ui = ui;
}


void Pen::drawPressEvent(DrawEvent event)
{
    if(event.button() == Qt::LeftButton and stroke == nullptr){
        lastPoint = event.position();
        stroke = new Stroke(this, color);
        stroke->init(event.docPos(),pressureToWidth(event.pressure()));
        ui->getDocument()->addItem(stroke);
    } else {
        drawReleaseEvent(event);
    }
}


void Pen::drawMoveEvent(DrawEvent event)
{
    if(stroke != nullptr){
        float dist = abs(event.position().x()-lastPoint.x()) + abs(event.position().y()-lastPoint.y());
        if (event.deviceType() == QInputDevice::DeviceType::Mouse and dist > 4){//min distance to add new point for mouse
            stroke->addpoint(event.docPos(),pressureToWidth(event.pressure()));
            lastPoint = event.position();
        } else if (event.deviceType() == QInputDevice::DeviceType::Stylus and dist > 2){//min distance to add new point for pen
            stroke->addpoint(event.docPos(),pressureToWidth(event.pressure()));
            lastPoint = event.position();
        }
    }
}


void Pen::drawReleaseEvent(DrawEvent event)
{
    if(stroke != nullptr){
        stroke->finish(event.docPos(),pressureToWidth(event.pressure()));
        stroke = nullptr;
    }
}


void Pen::drawDoubleClickEvent(DrawEvent event){
    Q_UNUSED(event);
}



float Pen::pressureToWidth(float pressure)
{
    return width + 1.5*pressure*width + 0.2;
}
