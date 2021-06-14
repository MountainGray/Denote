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
        timer.start();
        last_point = event.position();
        true_last_point = event.position();
        stroke = new Stroke(this);
        if(event.deviceType() == QInputDevice::DeviceType::Stylus) stroke->init(event.docPos(), event.pressure());
        else stroke->init(event.docPos(), fmax(speed_width*width,0.1));
        ui->getDocument()->addItem(stroke);
    } else {
        drawReleaseEvent(event);
    }
    count = 0;
    sum_dist = 1;
}


void Pen::drawMoveEvent(DrawEvent event)
{
    float num_speed_points = 4;
    float slow_thresh = 3; //seconds per 1000 pixels

    if(true_last_point == event.position()) return;
    if(count >= num_speed_points){
        inverse_speed = timer.restart()/(sum_dist*num_speed_points);
        speed_width = sqrt(fmin(inverse_speed,slow_thresh)/slow_thresh);
        speed_width = (speed_width + last_speed_width)/2;
        last_speed_width = speed_width;
        count = 0;
        sum_dist = 0;
    } else {
        sum_dist += fabs(event.position().x()-true_last_point.x());
        sum_dist += fabs(event.position().y()-true_last_point.y());
        count++;
    }

    if(stroke != nullptr){
        float dx = event.position().x()-last_point.x();
        float dy = event.position().y()-last_point.y();
        float dist = sqrt(dx*dx+dy*dy);

        if (event.deviceType() == QInputDevice::DeviceType::Mouse and dist > 3){//min distance to add new point for mouse
            stroke->addpoint(event.docPos(), fmax(speed_width*width,0.1));
            last_point = event.position();
        } else if (event.deviceType() == QInputDevice::DeviceType::Stylus and dist > 2){//min distance to add new point for pen
            //stroke->addpoint(event.docPos(),(pressureToWidth(event.pressure()) + fmax(speed_width*width,0.1))/2);//average
            stroke->addpoint(event.docPos(),fmax(event.pressure()*speed_width*width,0.1));//mult average
            //stroke->addpoint(event.docPos(),pressureToWidth(event.pressure()));//pressure
            //stroke->addpoint(event.docPos(),fmax(speed_width*width,0.1));//speed
            last_point = event.position();
        }
        true_last_point = event.position();
    }
}


void Pen::drawReleaseEvent(DrawEvent event)
{
    if(stroke != nullptr){

        if(event.deviceType() == QInputDevice::DeviceType::Mouse){
            stroke->finish(event.docPos(), 0.1);
        } else if(event.deviceType() == QInputDevice::DeviceType::Stylus){
            stroke->finish(event.docPos(),pressureToWidth(event.pressure()));
        }

        stroke = nullptr;
    }
}


void Pen::drawDoubleClickEvent(DrawEvent event){
    Q_UNUSED(event);
}



float Pen::pressureToWidth(float pressure)
{
    return pressure*width + 0.1;
}
