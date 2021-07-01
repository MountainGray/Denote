#include "eraser.h"

#include "Ui/ui.h"
#include "Framework/document.h"
#include "Framework/ToolMenus/erasermenu.h"
#include "Framework/documentgraphics.h"

#include <QPainter>


Eraser::Eraser(UI* ui) : Tool(ui)
{
    tool_menu = new EraserMenu(this);
    setWidth(10);
}


void Eraser::documentProximityEvent(QEvent *event)
{
    if(event->type() == QEvent::Enter) activate();
    else if(event->type() == QEvent::Leave) deactivate();
}


void Eraser::drawPressEvent(DrawEvent event)
{
    if(event.button() == Qt::LeftButton){
        erasing = true;
    }
}


void Eraser::drawMoveEvent(DrawEvent event)
{
    if(visible){
        setPos(event.docPos());
        if(erasing){
            QList<QGraphicsItem*> items = ui->getActiveDocument()->collidingItems(this,Qt::ItemSelectionMode::IntersectsItemBoundingRect);
            foreach(QGraphicsItem* item, items){
                if(item->type() == UserType + 1 or item->type() == UserType + 4 or item->type() == UserType + 5){ //stroke or fill
                    ui->getActiveDocument()->removeItem(item);
                    delete item;
                }
            }
        }
    }
}


void Eraser::drawReleaseEvent(DrawEvent event)
{
    if(event.button() == Qt::LeftButton){
        erasing = false;
    }
}


void Eraser::activate()
{
    if(not visible){
        ui->getActiveDocument()->addItem(this);
        visible = true;
    }
}


void Eraser::deactivate()
{
    if(visible){
        ui->getActiveDocument()->removeItem(this);
        visible = false;
    }
}


void Eraser::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,60,60));
    painter.setBrush(QBrush(QColor("Pink")));
    painter.drawRect(30-width/2,30-width/2, width,width);
    painter.drawText(QPointF(2,12),"Eraser");
}


QRectF Eraser::boundingRect() const
{
    return bounds;
}


void Eraser::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);

    if(widget->parentWidget() != ui->getActiveView()) return;

    QPen pen = QPen(QColor(0,0,0,55), 1, Qt::SolidLine, Qt::RoundCap);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(QPointF(0,0),0.5*width,0.5*width);
}


void Eraser::setWidth(float width)
{
    this->width = width;
    bounds = QRectF(-0.5*width,-0.5*width, width, width).adjusted(-2,-2,2,2);
    tool_preset->update();
}
