#include "circleselect.h"

#include "Ui/ui.h"
#include "Framework/document.h"
#include "Graphics/pagelayoutscene.h"
#include "Framework/toolmenu.h"
#include "Tools/selectionbox.h"
#include "Graphics/page.h"
#include "Graphics/pageportal.h"

#include <QPainter>


CircleSelect::CircleSelect(UI* ui, SelectionBox* box) : Tool(ui)
{
    this->box = box;

    width_slider = new QSlider(Qt::Horizontal);
    width_slider->setValue(width);
    width_slider->setMaximum(40);

    menu_layout = new QGridLayout();
    menu_layout->addWidget(width_slider,0,0);

    tool_menu->setLayout(menu_layout);

    connect(width_slider, &QSlider::valueChanged, this, &CircleSelect::updateWidth);

    setWidth(10);
}


void CircleSelect::documentProximityEvent(QEvent *event)
{
    if(event->type() == QEvent::Enter) activate();
    else if(event->type() == QEvent::Leave) deactivate();
}


void CircleSelect::drawPressEvent(ToolEvent event)
{
    selecting = true;
}


void CircleSelect::drawMoveEvent(ToolEvent event)
{
    if(visible){
        setPos(event.layoutPos());
        if(selecting){
            QRectF page_bounds = sceneBoundingRect().translated(-ui->getActivePortal()->scenePos());

            foreach(QGraphicsItem* item, ui->getActivePage()->items()){
                if(page_bounds.intersects(item->sceneBoundingRect())){//checks intersection on page level
                    if(item->type() == TypePenStroke or item->type() == TypeFillStroke or item->type() == TypeImage){ //stroke or fill or image
                        if(event.buttons() & Qt::LeftButton) item->setSelected(true);
                        else if(event.buttons() & Qt::RightButton) item->setSelected(false);
                    }
                }
            }
        }
    }
}


void CircleSelect::drawReleaseEvent(ToolEvent event)
{
    selecting = false;
}


void CircleSelect::drawDoubleClickEvent(ToolEvent event)
{
    if(event.button() == Qt::RightButton){
        ui->getActivePage()->clearSelection();
    } else if(event.button() == Qt::LeftButton){
        ui->setActiveTool(box);
    }
}


void CircleSelect::activate()
{
    if(not visible){
        ui->getActiveLayout()->addItem(this);
        visible = true;
    }
}


void CircleSelect::deactivate()
{
    if(visible){
        ui->getActiveLayout()->removeItem(this);
        visible = false;
    }
}


void CircleSelect::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,60,60));
    painter.setBrush(QBrush(QColor("Blue")));
    painter.drawEllipse(QPointF(30,30),width/2,width/2);
    painter.drawText(QPointF(2,12),"Circle Select");
}


QRectF CircleSelect::boundingRect() const
{
    return bounds;
}


void CircleSelect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen = QPen(QColor(0,0,255,55), 2, Qt::SolidLine, Qt::RoundCap);
    pen.setCosmetic(true);
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);
    painter->drawEllipse(QPointF(0,0),0.5*width,0.5*width);
}


void CircleSelect::setWidth(float width)
{
    this->width = width;
    width_slider->setValue(width);
    bounds = QRectF(-0.5*width,-0.5*width, width, width).adjusted(-2,-2,2,2);
    tool_preset->update();
    prepareGeometryChange();
}


void CircleSelect::updateWidth(int width)
{
    setWidth(float(width));
}
