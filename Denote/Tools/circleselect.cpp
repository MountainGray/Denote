#include "circleselect.h"

#include "Ui/ui.h"
#include "Framework/document.h"
#include "Framework/documentgraphics.h"
#include "Framework/toolmenu.h"
#include "Tools/selectionbox.h"

#include <QPainter>


CircleSelect::CircleSelect(UI* ui, SelectionBox* box) : Tool(ui)
{
    this->box = box;
    width = 10;

    width_slider = new QSlider(Qt::Horizontal);
    width_slider->setValue(width);
    width_slider->setMaximum(40);

    menu_layout = new QGridLayout();
    menu_layout->addWidget(width_slider,0,0);

    tool_menu->setLayout(menu_layout);

    connect(width_slider, &QSlider::valueChanged, this, &CircleSelect::updateWidth);
}


void CircleSelect::documentProximityEvent(QEvent *event)
{
    if(event->type() == QEvent::Enter) activate();
    else if(event->type() == QEvent::Leave) deactivate();
}


void CircleSelect::drawPressEvent(DrawEvent event)
{
    selecting = true;
}


void CircleSelect::drawMoveEvent(DrawEvent event)
{
    if(visible){
        setPos(event.docPos());
        if(selecting){
            QList<QGraphicsItem*> items = ui->getActiveDocument()->collidingItems(this,Qt::ItemSelectionMode::IntersectsItemBoundingRect);
            foreach(QGraphicsItem* item, items){
                if(item->type() == UserType + 1 or item->type() == UserType + 4 or item->type() == UserType + 5){ //stroke or fill or image
                    if(event.buttons() & Qt::LeftButton) item->setSelected(true);
                    else if(event.buttons() & Qt::RightButton) item->setSelected(false);
                }
            }
        }
    }
}


void CircleSelect::drawReleaseEvent(DrawEvent event)
{
    selecting = false;
}


void CircleSelect::drawDoubleClickEvent(DrawEvent event)
{
    if(event.button() == Qt::RightButton){
        ui->getActiveDocument()->clearSelection();
    } else if(event.button() == Qt::LeftButton){
        ui->setActiveTool(box);
    }
}


void CircleSelect::activate()
{
    if(not visible){
        ui->getActiveDocument()->addItem(this);
        visible = true;
    }
}


void CircleSelect::deactivate()
{
    if(visible){
        ui->getActiveDocument()->removeItem(this);
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
    painter.drawText(QPointF(2,12),"CircleSelect");
}


QRectF CircleSelect::boundingRect() const
{
    return bounds;
}


void CircleSelect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);

    if(widget->parentWidget() != ui->getActiveView()) return;

    QPen pen = QPen(QColor(0,0,255,55), 1, Qt::SolidLine, Qt::RoundCap);
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
}


void CircleSelect::updateWidth(int width)
{
    this->width = float(width);
}
