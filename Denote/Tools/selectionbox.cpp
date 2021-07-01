#include "selectionbox.h"
#include "Framework/ToolMenus/toolmenu.h"
#include "Framework/documentgraphics.h"
#include "Framework/document.h"
#include "Ui/ui.h"
#include <QPainter>


SelectionBox::SelectionBox(UI* ui) : Tool(ui)
{
    tool_menu = new ToolMenu(this);
}


void SelectionBox::drawPressEvent(DrawEvent event)
{

    if(event.button() == Qt::LeftButton and contains(mapFromScene(event.docPos()))){
        moving = true;
        first_point_diff = event.docPos()-pos();
    }
}


void SelectionBox::drawMoveEvent(DrawEvent event)
{
    if(moving){
        setPos(event.docPos()-first_point_diff);
    }
}


void SelectionBox::drawReleaseEvent(DrawEvent event)
{
    moving = false;
}


void SelectionBox::activate()
{
    visible = true;
    ui->getActiveDocument()->addItem(this);
    foreach(QGraphicsItem *item, ui->getActiveDocument()->selectedItems()){
        addToGroup(item);
    }
}


void SelectionBox::deactivate()
{
    visible = false;
    foreach(QGraphicsItem *item, ui->getActiveDocument()->selectedItems()){
        removeFromGroup(item);
    }
    ui->getActiveDocument()->removeItem(this);
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

    if(widget->parentWidget() != ui->getActiveView() or not visible) return;

    QPen pen = QPen(QColor(0,0,0,120), 2, Qt::DashLine, Qt::RoundCap);
    QBrush brush = QBrush(QColor(0,30,255,40));
    painter->setPen(pen);
    painter->setBrush(brush);
    if(not boundingRect().isNull()){
        painter->drawRect(boundingRect());
    }
}
