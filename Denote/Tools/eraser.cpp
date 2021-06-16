#include "eraser.h"

#include "Ui/ui.h"
#include "Framework/document.h"
#include "Framework/ToolMenus/erasermenu.h"

#include <QPainter>


Eraser::Eraser(UI* ui)
{
    this->ui = ui;
    tool_menu = new EraserMenu(this);
    setWidth(2);
}


void Eraser::drawPressEvent(DrawEvent event)
{
    if(event.button() == Qt::LeftButton){
        active = true;
    }
    if(added == false){
        ui->getDocument()->addItem(this);
        added = true;
    }
}


void Eraser::drawMoveEvent(DrawEvent event)
{
    if(active){
        setPos(event.docPos());
        QList<QGraphicsItem*> items = ui->getDocument()->collidingItems(this,Qt::ItemSelectionMode::IntersectsItemBoundingRect);
        foreach(QGraphicsItem* item, items){
            if(item->type() == UserType + 1){ //stroke
                ui->getDocument()->removeItem(item);
            }
        }
    }
}


void Eraser::drawReleaseEvent(DrawEvent event)
{
    if(event.button() == Qt::LeftButton){
        active = false;
    }
}


void Eraser::drawDoubleClickEvent(DrawEvent event)
{
    Q_UNUSED(event);
    return;
}


QRectF Eraser::boundingRect() const
{
    return bounds;
}


void Eraser::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen = QPen(QColor(0,0,0,55), 1, Qt::SolidLine, Qt::RoundCap);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(QPointF(0,0),0.5*width,0.5*width);
}


void Eraser::setWidth(float width)
{
    this->width = width;
    bounds = QRectF(-0.5*width,-0.5*width, width, width).adjusted(-2,-2,2,2);
}
