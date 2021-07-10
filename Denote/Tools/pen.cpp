#include "Tools/pen.h"

#include "Tools/stroke.h"
#include "Ui/ui.h"
#include "Framework/document.h"
#include "Framework/toolmenu.h"
#include "Graphics/page.h"
#include <QPainter>
#include <QColorDialog>


Pen::Pen(UI* ui) : Tool(ui)
{
    width = 4;
    color = QColor("red");

    width_slider = new QSlider(Qt::Horizontal);
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
        ui->getActiveDocument()->getActivePage()->addToGroup(stroke);
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

    if(stroke != nullptr){
        float dx = event.position().x()-last_point.x();
        float dy = event.position().y()-last_point.y();
        float dist = sqrt(dx*dx+dy*dy);

        if (event.deviceType() == QInputDevice::DeviceType::Mouse and dist >= 3){//min distance to add new point for mouse
            if(mode == "Speed") stroke->addpoint(event.docPos(), fmax(speed_width*width,0.1));
            else stroke->addpoint(event.docPos(), width);
            last_point = event.position();
        } else if (event.deviceType() == QInputDevice::DeviceType::Stylus and dist >= 1){//min distance to add new point for pen
            if(mode == "Speed") stroke->addpoint(event.docPos(),fmax(speed_width*width,0.1));//speed
            else if(mode == "Pressure") stroke->addpoint(event.docPos(),pressureToWidth(event.pressure()));//pressure
            else if(mode == "Average") stroke->addpoint(event.docPos(),(pressureToWidth(event.pressure()) + fmax(speed_width*width,0.1))/2);//average
            else if(mode == "Combined") stroke->addpoint(event.docPos(),fmax(event.pressure()*speed_width*width,0.1));//mult average
            //else stroke->addpoint(event.docPos(), width);
            //else stroke->addpoint(event.docPos(), fmax(0.1,abs(width*event.xTilt()/60)));
            else stroke->addpoint(event.docPos(), fmax(0.1, width*(abs(cosf(dir))*0.9+0.1)));
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


void Pen::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,60,60));
    painter.setBrush(QBrush(color));
    painter.drawEllipse(QPointF(30,30),width/2,width/2);
    painter.drawText(QPointF(2,12),"Pen");
}


void Pen::setWidth(float width)
{
    this->width = width;
    width_slider->setValue(width);
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


void Pen::updateWidth(int width)
{
    this->width = float(width);
}


void Pen::updateColor()
{
    color = QColorDialog::getColor(color);
}


void Pen::updateMode()
{
    mode = mode_combo->currentText();
}
