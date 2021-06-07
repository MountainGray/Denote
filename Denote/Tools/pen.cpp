#include "Tools/pen.h"

#include "Tools/stroke.h"
#include "Ui/ui.h"
#include "Framework/document.h"


Pen::Pen(UI* ui)
{
    this->ui = ui;
}


//tablet and mouse functions are basically the same besides adding pressure, should fix in future;


void Pen::tabletPressEvent(QTabletEvent *event)
{
    if(event->button() == Qt::LeftButton and stroke == nullptr){
        stroke = new Stroke(this);
        stroke->init(event->position(),event->pressure());
        ui->getDocument()->addItem(stroke);
    }
}


void Pen::tabletMoveEvent(QTabletEvent *event)
{
    if (stroke != nullptr){
        stroke->addpoint(event->position(),event->pressure());
    }
}


void Pen::tabletReleaseEvent(QTabletEvent *event)
{
    if((event->button() == Qt::LeftButton) and (stroke != nullptr)){
        stroke->finish(event->position(),event->pressure());
        stroke = nullptr;
    }
}


void Pen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton and stroke == nullptr){
        stroke = new Stroke(this);
        stroke->init(event->scenePos(),0);
        ui->getDocument()->addItem(stroke);
    }
}


void Pen::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (stroke != nullptr){
        stroke->addpoint(event->scenePos(),0);
    }
}


void Pen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if((event->button() == Qt::LeftButton) and (stroke != nullptr)){
        stroke->finish(event->scenePos(),0);
        stroke = nullptr;
    }
}


void Pen::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event){
    Q_UNUSED(event);
}
