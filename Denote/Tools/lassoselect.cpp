#include "lassoselect.h"

#include "Ui/ui.h"
#include "Framework/document.h"
#include "Framework/documentgraphics.h"
#include "Framework/toolmenu.h"
#include "Tools/selectionbox.h"

#include <QPainter>

LassoSelect::LassoSelect(UI* ui, SelectionBox* box) : Tool(ui)
{
    this->box = box;
}


void LassoSelect::documentProximityEvent(QEvent *event)
{
    if(event->type() == QEvent::Enter) activate();
    else if(event->type() == QEvent::Leave) deactivate();
}


void LassoSelect::drawPressEvent(DrawEvent event)
{
    Q_UNUSED(event);
    selecting = true;
}


void LassoSelect::drawMoveEvent(DrawEvent event)
{
    if(added){
        if(selecting){
            lasso << event.docPos();
            bounds = lasso.boundingRect();
            update(bounds);

            QList<QGraphicsItem*> items = ui->getActiveDocument()->collidingItems(this,Qt::ItemSelectionMode::IntersectsItemBoundingRect);
            foreach(QGraphicsItem* item, items){
                if(item->type() == TypePenStroke or item->type() == TypeFillStroke or item->type() == TypeImage){ //stroke or fill or image
                    if(event.buttons() & Qt::LeftButton) item->setSelected(true);
                    else if(event.buttons() & Qt::RightButton) item->setSelected(false);
                }
            }
        }
    }
}


void LassoSelect::drawReleaseEvent(DrawEvent event)
{
    Q_UNUSED(event);
    selecting = false;
    lasso.clear();
}


void LassoSelect::drawDoubleClickEvent(DrawEvent event)
{
    if(event.button() == Qt::RightButton){
        ui->getActiveDocument()->clearSelection();
    } else if(event.button() == Qt::LeftButton){
        ui->setActiveTool(box);
    }
}


void LassoSelect::activate()
{
    if(not added){
        ui->getActiveDocument()->addItem(this);
        added = true;
    }
}


void LassoSelect::deactivate()
{
    if(added){
        ui->getActiveDocument()->removeItem(this);
        added = false;
    }
}


void LassoSelect::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,60,60));
    painter.drawText(QPointF(2,12),"Lasso Select");
    painter.setPen(QPen(QColor("blue")));
    painter.setBrush(QBrush(QColor(0,30,255,40)));
    painter.drawEllipse(QPointF(30,30),15,10);
}


QRectF LassoSelect::boundingRect() const
{
    return bounds;
}


void LassoSelect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);

    if(widget->parentWidget() != ui->getActiveView()) return;

    QPen pen = QPen(QColor(0,0,255,55), 2, Qt::SolidLine, Qt::RoundCap);
    QBrush brush = QBrush(QColor(0,30,255,40));
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->setBrush(brush);
    painter->drawPolygon(lasso);
}
