#include "pen.h"

#include "stroke.h"
#include "ui.h"
#include "document.h"


Pen::Pen(UI* ui)
{
    this->ui = ui;
}

void Pen::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        if(stroke == nullptr){
            stroke = new Stroke(this);
            stroke->init(event);
            ui->getDocument()->addItem(stroke);
        }
    }
}

void Pen::mouseMoveEvent(QGraphicsSceneMouseEvent *event){

    if (stroke != nullptr){
        stroke->addpoint(event);
    }

}

void Pen::mouseReleaseEvent(QGraphicsSceneMouseEvent *event){
    if((event->button() == Qt::LeftButton) and (stroke != nullptr)){
        stroke->finish(event);
        stroke = nullptr;
    }
}
