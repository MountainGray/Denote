#include "fill.h"

#include "Tools/fillstroke.h"
#include "Framework/document.h"
#include "Framework/toolmenu.h"
#include "Graphics/page.h"
#include <QColorDialog>
#include <QPainter>
#include "Ui/ui.h"
#include "Graphics/pageportal.h"


Fill::Fill(UI* ui) : Tool(ui)
{
    color = QColor("red");

    color_button = new QPushButton("Select Color");

    menu_layout = new QGridLayout();
    menu_layout->addWidget(color_button,0,0);

    tool_menu->setLayout(menu_layout);

    connect(color_button, &QPushButton::clicked, this, &Fill::updateColor);
}


void Fill::drawPressEvent(ToolEvent event)
{
    if(event.button() == Qt::LeftButton and fill_stroke == nullptr){
        last_point = event.position();

        fill_stroke = new FillStroke(this);
        new UndoCreation(ui->getActiveDocument()->getHistoryManager(), fill_stroke, "Fill Stroke");

        if(event.deviceType() == QInputDevice::DeviceType::Stylus) fill_stroke->init(event.pagePos());
        else fill_stroke->init(event.pagePos());
        ui->getActivePage()->addItem(fill_stroke);
    } else {
        drawReleaseEvent(event);
    }
}


void Fill::drawMoveEvent(ToolEvent event)
{
    if(fill_stroke != nullptr){
        float dx = event.position().x()-last_point.x();
        float dy = event.position().y()-last_point.y();
        float dist = sqrt(dx*dx+dy*dy);

        if (event.deviceType() == QInputDevice::DeviceType::Mouse and dist >= 3){//min distance to add new point for mouse
            fill_stroke->addpoint(event.pagePos());
            last_point = event.position();
        } else if (event.deviceType() == QInputDevice::DeviceType::Stylus and dist >= 1){//min distance to add new point for pen
            fill_stroke->addpoint(event.pagePos());
            last_point = event.position();
        }

        //ui->getActivePage()->updatePortals(fill_stroke->sceneBoundingRect());
        ui->getActivePortal()->update(fill_stroke->sceneBoundingRect());
    }
}


void Fill::drawReleaseEvent(ToolEvent event)
{
    if(fill_stroke != nullptr){
        if(event.deviceType() == QInputDevice::DeviceType::Mouse){
            fill_stroke->finish(event.pagePos());
        } else if(event.deviceType() == QInputDevice::DeviceType::Stylus){
            fill_stroke->finish(event.pagePos());
        }
        ui->getActivePage()->updatePortals(fill_stroke->sceneBoundingRect());
        ui->getActivePage()->updateLowestObject(fill_stroke);
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
    painter.drawRect(QRectF(0,0,tool_preset->width(),tool_preset->height()));
    painter.setBrush(QBrush(color));
    painter.drawEllipse(QPointF(tool_preset->width()/2,tool_preset->height()/2),10,10);
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
    tool_preset->update();
}
