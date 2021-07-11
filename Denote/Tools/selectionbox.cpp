#include "selectionbox.h"
#include "Framework/toolmenu.h"
#include "Graphics/pagelayoutscene.h"
#include "Graphics/page.h"
#include "Framework/document.h"
#include "Ui/ui.h"
#include <QPainter>


SelectionBox::SelectionBox(UI* ui) : Tool(ui)
{

}


void SelectionBox::drawPressEvent(ToolEvent event)
{

    if(event.button() == Qt::LeftButton and contains(mapFromScene(event.layoutPos()))){
        moving = true;
        first_point_diff = event.layoutPos()-pos();
    } else {
        ui->getActivePage()->clearSelection();
        deactivate();
    }
}


void SelectionBox::drawMoveEvent(ToolEvent event)
{
    if(moving){
        setPos(event.layoutPos()-first_point_diff);
    }
}


void SelectionBox::drawReleaseEvent(ToolEvent event)
{
    moving = false;
}


void SelectionBox::activate()
{
    if(not ui->getActiveLayout()->selectedItems().isEmpty()){
        visible = true;
        ui->getActiveLayout()->addItem(this);
        foreach(QGraphicsItem *item, ui->getActivePage()->selectedItems()){
            if(item->type() != TypePage or true){
                addToGroup(item);
            }
        }
    }
}


void SelectionBox::deactivate()
{
    visible = false;
    foreach(QGraphicsItem *item, childItems()){
        removeFromGroup(item);
        //needs to return to original group;
    }
    ui->getActiveLayout()->removeItem(this);
    setPos(0,0);
}


void SelectionBox::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,60,60));
    painter.setBrush(QBrush(QColor("grey")));
    painter.setPen(QPen(QColor("blue")));
    painter.drawRect(20,20, 20, 20);
    painter.setPen(QPen(QColor("black")));
    painter.drawText(QPointF(2,12),"Selection Box");
}


void SelectionBox::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen = QPen(QColor(0,0,0,120), 2, Qt::DashLine, Qt::RoundCap);
    QBrush brush = QBrush(QColor(0,30,255,40));
    painter->setPen(pen);
    painter->setBrush(brush);
    if(not boundingRect().isNull()){
        painter->drawRect(boundingRect());
    }
}
