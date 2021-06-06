#include "Tools/pen.h"

#include "Tools/stroke.h"
#include "Ui/ui.h"
#include "Framework/document.h"


Pen::Pen(UI* ui)
{
    this->ui = ui;
}


void Pen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(stroke == nullptr){
            stroke = new Stroke(this);
            stroke->init(event->scenePos(),0);
            ui->getDocument()->addItem(stroke);
        }
    }
    event->accept();
}


void Pen::mouseMoveEvent(QGraphicsSceneMouseEvent *event){
    if (stroke != nullptr){
        stroke->addpoint(event->scenePos(),0);
    }
    event->accept();
}


void Pen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if((event->button() == Qt::LeftButton) and (stroke != nullptr)){
        stroke->finish(event->scenePos(),0);
        stroke = nullptr;
    }
    event->accept();
}


void Pen::tabletPress(QTabletEvent *event)
{
    if(stroke == nullptr){
        stroke = new Stroke(this);
        stroke->init(event->position(),event->pressure());
        ui->getDocument()->addItem(stroke);
    }
    event->accept();
}


void Pen::tabletMove(QTabletEvent *event)
{
    if (stroke != nullptr){
        stroke->addpoint(event->position(),event->pressure());
    }
    event->accept();
}


void Pen::tabletRelease(QTabletEvent *event)
{
    if(stroke != nullptr){
        stroke->finish(event->position(),event->pressure());
        stroke = nullptr;
    }
    event->accept();
}
