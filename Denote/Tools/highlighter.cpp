#include "highlighter.h"

#include "Framework/toolmenu.h"
#include "Graphics/pagelayoutscene.h"
#include "Ui/ui.h"
#include "Graphics/page.h"
#include "Graphics/pageportal.h"
#include "Tools/rectangle.h"

#include <QPainter>
#include <QColorDialog>


Highlighter::Highlighter(UI* ui) : Tool(ui)
{
    color = QColor(255,255,0);

    width_slider = new QSlider(Qt::Horizontal);
    width_slider->setValue(width);
    width_slider->setMaximum(40);

    color_button = new QPushButton("Select Color");

    menu_layout = new QGridLayout();
    menu_layout->addWidget(width_slider,0,0);
    menu_layout->addWidget(color_button,1,0);

    tool_menu->setLayout(menu_layout);

    connect(width_slider, &QSlider::valueChanged, this, &Highlighter::updateWidth);
    connect(color_button, &QPushButton::clicked, this, &Highlighter::updateColor);

    setWidth(25);
}


void Highlighter::documentProximityEvent(QEvent *event)
{
    if(event->type() == QEvent::Enter) activate();
    else if(event->type() == QEvent::Leave) deactivate();
}


void Highlighter::drawPressEvent(ToolEvent event)
{
    Q_UNUSED(event);
    highlight = new Rectangle();
    highlight->setColor(color);
    ui->getActivePage()->addItem(highlight);
}


void Highlighter::drawMoveEvent(ToolEvent event)
{
    bool added = false;
    if(visible){
        if(event.modifiers() & Qt::ControlModifier and event.buttons() & Qt::LeftButton){
            if(adjusting_width){
                setWidth(pause_width-(event.position().y() - width_point.y())/4.0);
            } else {
                width_point = event.position();
                adjusting_width = true;
                pause_width = width;
            }
        } else {
            adjusting_width = false;
            setPos(event.layoutPos());
            if(highlight != nullptr){
                QRectF page_bounds = mapToScene(boundingRect()).translated(-ui->getActivePortal()->scenePos()).boundingRect();
                foreach(QGraphicsItem* item, ui->getActivePage()->items()){
                    if(page_bounds.intersects(item->boundingRect()) and item->type() != TypeRectangle){
                        PageItem* page_item = static_cast<PageItem*>(item);
                        if(page_item != nullptr and page_item->isPresent()){
                            highlight_area = highlight_area.united(page_item->sceneBoundingRect());
                            added = true;
                        }
                    }
                }
                if(added){
                    highlight->setRect(highlight_area);
                    ui->getActivePage()->updatePortals(highlight->sceneBoundingRect());
                }
            }
        }
    }
}


void Highlighter::drawReleaseEvent(ToolEvent event)
{
    Q_UNUSED(event);

    if(highlight != nullptr){
        if(highlight_area.isNull()){
            delete highlight;
        }else{
            new UndoCreation(ui->getActiveDocument()->getHistoryManager(), highlight, "Highlight");
        }
    }

    highlight_area = QRectF();
    highlight = nullptr;
}


void Highlighter::activate()
{
    if(not visible and ui->getActiveLayout() != nullptr){
        ui->getActiveLayout()->addItem(this);
        visible = true;
    }
}


void Highlighter::deactivate()
{
    if(visible and ui->getActiveLayout() != nullptr){
        ui->getActiveLayout()->removeItem(this);
        visible = false;
    }
}


void Highlighter::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,60,60));

    QColor transparent = color;
    transparent.setAlpha(120);

    painter.setBrush(QBrush(transparent));
    painter.setPen(Qt::NoPen);
    painter.drawRect(QRectF(10,10,40,40));
    painter.setPen(QPen(QColor("black")));
    painter.drawText(QPointF(2,12),"Highlighter");
}


QRectF Highlighter::boundingRect() const
{
    return bounds;
}


void Highlighter::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    QPen pen = QPen(QColor("black"), 1, Qt::SolidLine, Qt::RoundCap);
    pen.setCosmetic(true);
    painter->setPen(pen);

    QColor transparent = color;
    transparent.setAlpha(80);

    painter->setBrush(QBrush(transparent));
    painter->drawEllipse(QPointF(0,0),0.5*width,0.5*width);
}


void Highlighter::setWidth(float new_width)
{
    width = fmax(fmin(new_width,width_slider->maximum()),0);
    width_slider->setValue(width);
    bounds = QRectF(-0.5*width,-0.5*width, width, width).adjusted(-2,-2,2,2);
    tool_preset->update();
    prepareGeometryChange();
}


void Highlighter::updateWidth(int new_width)
{
    setWidth(float(new_width));
}


void Highlighter::updateColor()
{
    color = QColorDialog::getColor(color);
    tool_preset->update();
}
