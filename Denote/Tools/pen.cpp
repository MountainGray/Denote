#include "Tools/pen.h"

#include "Tools/stroke.h"
#include "Ui/ui.h"
#include "Framework/document.h"
#include "Framework/toolmenu.h"
#include "Graphics/page.h"
#include <QPainter>
#include <QColorDialog>
#include "Graphics/pageportal.h"


Pen::Pen(UI* ui) : Tool(ui)
{
    color = QColor("red");

    width_slider = new QSlider(Qt::Horizontal);
    width_slider->setSingleStep(1);
    width_slider->setPageStep(1);
    width_slider->setValue(width);
    width_slider->setMaximum(40);


    color_button = new QPushButton("Select Color");

    mode_combo = new QComboBox();
    mode_combo->addItems({QString("Constant"),QString("Pressure"),QString("Speed"),QString("Average"),QString("Combined")});
    mode_combo->setCurrentIndex(1);

    menu_layout = new QGridLayout();
    menu_layout->addWidget(mode_combo,0,0);
    menu_layout->addWidget(width_slider,1,0);
    menu_layout->addWidget(color_button,2,0);

    tool_menu->setLayout(menu_layout);

    connect(width_slider, &QSlider::valueChanged, this, &Pen::updateWidth);
    connect(color_button, &QPushButton::clicked, this, &Pen::updateColor);
    connect(mode_combo, &QComboBox::currentIndexChanged, this, &Pen::updateMode);

    setWidth(3);
}


void Pen::drawPressEvent(ToolEvent event)
{
    if(event.button() == Qt::LeftButton and stroke == nullptr){
        timer.start();
        last_point = event.position();
        true_last_point = event.position();

        stroke = new Stroke(this);
        new UndoCreation(ui->getActiveDocument()->getHistoryManager(), stroke, "Pen Stroke");

        if(event.deviceType() == QInputDevice::DeviceType::Stylus) stroke->init(event.pagePos(), event.pressure());
        else stroke->init(event.pagePos(), fmax(speed_width*width,0.1));
        ui->getActivePage()->addItem(stroke);
    } else {
        drawReleaseEvent(event);
    }
    count = 0;
    sum_dist = 1;
}


void Pen::drawMoveEvent(ToolEvent event)
{
    if(event.modifiers() & Qt::ControlModifier and event.buttons() & Qt::LeftButton){
        if(adjusting_width){
            setWidth(pause_width-(event.position().y() - width_point.y())/4.0);
        } else {
            width_point = event.position();
            adjusting_width = true;
            pause_width = width;
        }
    } else {
        adjusting_width = false;
        float num_speed_points = 4;
        float slow_thresh = 3; //seconds per 1000 pixels

        if(true_last_point == event.position()) return;
        if(mode == "Speed" or mode == "Average" or mode == "Combined"){
            if(count >= num_speed_points){
                inverse_speed = timer.restart()/(sum_dist*num_speed_points);
                speed_width = sqrt(fmin(inverse_speed,slow_thresh)/slow_thresh);
                speed_width = (speed_width + last_speed_width)/2;
                last_speed_width = speed_width;
                count = 0;
                sum_dist = 0;
                dir = atan2f(last_point.y()-event.position().y(), event.position().x()-last_point.x());
                dir = (dir + last_dir)/2;
                last_dir = dir;
                //if(dir < 0) dir += 6.28;
                //qDebug() << dir;
            } else {
                sum_dist += fabs(event.position().x()-true_last_point.x());
                sum_dist += fabs(event.position().y()-true_last_point.y());
                count++;
            }
        }

        if(stroke != nullptr){
            //float dx = event.position().x()-last_point.x();
            //float dy = event.position().y()-last_point.y();
            //float dist = sqrt(dx*dx+dy*dy);
            //float dist = abs(dx)+abs(dy);

            float dist = 1;

            if (event.deviceType() == QInputDevice::DeviceType::Mouse and dist >= 1){//min distance to add new point for mouse
                if(mode == "Speed") stroke->addpoint(event.pagePos(), fmax(speed_width*width,0.1));
                else stroke->addpoint(event.pagePos(), width);
                last_point = event.position();
            } else if (event.deviceType() == QInputDevice::DeviceType::Stylus and dist >= 1){//min distance to add new point for pen
                if(mode == "Speed") stroke->addpoint(event.pagePos(),fmax(speed_width*width,0.1));//speed
                else if(mode == "Pressure") stroke->addpoint(event.pagePos(),pressureToWidth(event.pressure()));//pressure
                else if(mode == "Average") stroke->addpoint(event.pagePos(),(pressureToWidth(event.pressure()) + fmax(speed_width*width,0.1))/2);//average
                else if(mode == "Combined") stroke->addpoint(event.pagePos(),fmax(event.pressure()*speed_width*width,0.1));//mult average
                //else stroke->addpoint(event.docPos(), width);
                //else stroke->addpoint(event.docPos(), fmax(0.1,abs(width*event.xTilt()/60)));
                else stroke->addpoint(event.pagePos(), fmax(0.1, width*(abs(cosf(dir))*0.9+0.1)));
                last_point = event.position();
            }
            //ui->getActivePage()->updatePortals(QRectF(event.pagePos(),last_page_pos).normalized().adjusted(-3,-3,3,3));
            ui->getActivePortal()->update(QRectF(event.pagePos(),last_page_pos).normalized().adjusted(-3,-3,3,3));

            true_last_point = event.position();
            last_page_pos = event.pagePos();
        }
    }

}


void Pen::drawReleaseEvent(ToolEvent event)
{
    if(stroke != nullptr){
        if(event.deviceType() == QInputDevice::DeviceType::Mouse){
            stroke->finish(event.pagePos(), 0.1);
        } else if(event.deviceType() == QInputDevice::DeviceType::Stylus){
            stroke->finish(event.pagePos(),pressureToWidth(event.pressure()));
        }
        ui->getActivePage()->updatePortals(stroke->sceneBoundingRect());
        ui->getActivePage()->updateLowestObject(stroke);
        stroke = nullptr;
    }
}


void Pen::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,tool_preset->width(),tool_preset->height()));
    painter.setBrush(QBrush(color.active()));
    painter.drawEllipse(QPointF(tool_preset->width()/2,tool_preset->height()/2),width/2,width/2);
    painter.drawText(QPointF(2,12),"Pen");
}


void Pen::setDisplayMode(IColor::DisplayMode mode)
{
    color.setDisplayMode(mode);
    tool_preset->update();
}


void Pen::setWidth(float new_width)
{
    width = fmax(fmin(new_width, width_slider->maximum()),0);
    width_slider->setValue(width*3);
    tool_preset->update();
}


void Pen::setColor(QColor color)
{
    this->color = color;
    tool_preset->update();
}


float Pen::pressureToWidth(float pressure)
{
    return pressure*width + 0.1;
}


void Pen::updateWidth(int new_width)
{
    setWidth(float(new_width)/3);
}


void Pen::updateColor()
{
    color = IColor(QColorDialog::getColor(color.active()),ui->getDisplayMode());
}


void Pen::updateMode()
{
    mode = mode_combo->currentText();
}
