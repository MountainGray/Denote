#include "document.h"
#include "ui.h"

Document::Document(UI* ui, QObject* parent):QGraphicsScene(parent){
    this->ui = ui;
}


Document::~Document(){

}

void Document::mousePressEvent(QGraphicsSceneMouseEvent *event){
    ui->mousePressEvent(event);
}

void Document::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    ui->mouseReleaseEvent(event);
}

void Document::drawBackground(QPainter *painter, const QRectF &rect){
    painter->fillRect(rect, QBrush(Qt::black));
    painter->drawPixmap(QPoint(0,0), background);
    painter->drawPixmap(QPoint(0,background.height()+50), background); //page 2
}

void Document::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
   ui->mouseMoveEvent(event);
}

