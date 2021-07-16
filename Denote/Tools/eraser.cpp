#include "eraser.h"

#include "Ui/ui.h"
#include "Framework/document.h"
#include "Framework/toolmenu.h"
#include "Graphics/pagelayoutscene.h"
#include "Graphics/page.h"
#include "Graphics/pageportal.h"

#include <QPainter>


Eraser::Eraser(UI* ui) : Tool(ui)
{
    width_slider = new QSlider(Qt::Horizontal);
    width_slider->setValue(width);
    width_slider->setMaximum(40);

    menu_layout = new QGridLayout();
    menu_layout->addWidget(width_slider,0,0);

    tool_menu->setLayout(menu_layout);

    connect(width_slider, &QSlider::valueChanged, this, &Eraser::updateWidth);

    setWidth(10);
}


void Eraser::documentProximityEvent(QEvent *event)
{
    if(event->type() == QEvent::Enter) activate();
    else if(event->type() == QEvent::Leave) deactivate();
}


void Eraser::drawPressEvent(ToolEvent event)
{
    if(event.button() == Qt::LeftButton){
        erasing = true;
    }
}


void Eraser::drawMoveEvent(ToolEvent event)
{
    if(visible){
        setPos(event.layoutPos());
        if(erasing){
            QPainterPath page_shape = mapToScene(shape()).translated(-ui->getActivePortal()->scenePos());
            foreach(QGraphicsItem* item, ui->getActivePage()->items()){
                if(page_shape.intersects(item->mapToScene(item->shape()))){//checks intersection on page level
                    if(item->isVisible() and (item->type() == TypePenStroke or item->type() == TypeFillStroke or item->type() == TypeImage)){
                        item->hide();
                        erased.append(item);
                    }
                }
            }
        }
    }
}


void Eraser::drawReleaseEvent(ToolEvent event)
{
    if(event.button() == Qt::LeftButton){
        if(not erased.isEmpty()){
            new EraserUndo(ui->getHistoryManager(), erased);
            ui->getActivePage()->updatePortals();
            erased.clear();
        }
        erasing = false;
    }
}


void Eraser::activate()
{
    if(not visible){
        ui->getActiveLayout()->addItem(this);
        visible = true;
    }
}


void Eraser::deactivate()
{
    if(visible){
        ui->getActiveLayout()->removeItem(this);
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


QPainterPath Eraser::shape() const
{
    QPainterPath path;
    path.addEllipse(bounds);
    return path;
}


void Eraser::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen = QPen(QColor(0,0,0,55), 2, Qt::SolidLine, Qt::RoundCap);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(QPointF(0,0),0.5*width,0.5*width);
}


void Eraser::setWidth(float width)
{
    this->width = width;
    width_slider->setValue(width);
    bounds = QRectF(-0.5*width,-0.5*width, width, width).adjusted(-2,-2,2,2);
    tool_preset->update();
    prepareGeometryChange();
}


void Eraser::updateWidth(int width)
{
    setWidth(float(width));
}








EraserUndo::EraserUndo(HistoryManager* manager, QList<QGraphicsItem *> erased) : UndoObject(manager)
{
    this->erased = erased;
    setText("Erased Strokes");
}


void EraserUndo::undo()
{
    foreach(QGraphicsItem* item, erased){
        item->show();
    }
    setText("Re-added Strokes");
}


void EraserUndo::redo()
{
    foreach(QGraphicsItem* item, erased){
        item->hide();
    }
    setText("Erased Strokes");
}
