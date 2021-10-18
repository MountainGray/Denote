#include "Tools/pen.h"

#include <QPainter>
#include <QColorDialog>

#include "Graphics/pageportal.h"
#include "Framework/documentview.h"
#include "Ui/ui.h"
#include "Framework/document.h"
#include "Framework/toolmenu.h"
#include "Graphics/page.h"
#include "Graphics/pagelayoutscene.h"


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




void Pen::drawPressEvent(ToolEvent event){
    if(event.button() == Qt::LeftButton and pen_stroke == nullptr){
        pen_stroke = new PenStroke();
        new UndoCreation(ui->getActiveDocument()->getHistoryManager(), pen_stroke, "Pen Stroke");
        BezierPoint p;
        p.x = event.pagePos().x();
        p.y = event.pagePos().y();
        p.t = event.pressure();

        pen_stroke->initialize(p);
        view->setCachedStroke(pen_stroke);
        ui->getActivePage()->addItem(pen_stroke);


        //QRectF clipping = ui->getActivePortal()->mapRectToScene(ui->getActivePage()->getPageBounds());
        //pen_stroke->setClipping(clipping);
        last_pos = event.pagePos().toPoint();

    } else {
        drawReleaseEvent(event);
    }
}



void Pen::drawMoveEvent(ToolEvent event){
    if(pen_stroke == nullptr) return;

    /*
    if(event.type() == QEvent::MouseMove or true){
        update_cycle++;
        if(update_cycle < 10) return;
        update_cycle = 0;
    }*/

    if(abs(event.pagePos().x() - last_pos.x()) + abs(event.pagePos().y() - last_pos.y()) < 2) return;

    BezierPoint p;
    p.x = event.pagePos().x();
    p.y = event.pagePos().y();
    p.t = event.pressure()*6;
    pen_stroke->append(p);

    QRect dirty = QRect(event.pagePos().toPoint(),last_pos).normalized().adjusted(-2,-2,2,2);

    if(!dirty.isNull()){
        //view->scene()->update(view->mapToScene(dirty).boundingRect());
        ui->getActivePortal()->update(dirty);
    }

    last_pos = event.pagePos().toPoint();
}


void Pen::drawReleaseEvent(ToolEvent event){
    if(pen_stroke == nullptr) return;

    BezierPoint p;
    p.x = event.pagePos().x();
    p.y = event.pagePos().y();
    p.t = event.pressure();
    pen_stroke->terminate(p);


    view->clearCachedStroke();
    //pen_stroke->setTransform(view->getViewInverse());
    //ui->getActivePage()->addItem(pen_stroke);


    ui->getActivePage()->updatePortals();
    ui->getActivePage()->updateLowestObject(pen_stroke);
    pen_stroke = nullptr;
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
