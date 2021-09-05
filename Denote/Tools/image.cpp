#include "image.h"

#include "Framework/toolmenu.h"
#include "Framework/document.h"
#include "Graphics/page.h"
#include "Ui/ui.h"
#include <QPainter>


Image::Image(UI* ui) : Tool(ui) //really shouldn't be a tool
{

}


void Image::paintPreset(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(tool_preset);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(QColor("white")));
    painter.setPen(QPen(QColor("black")));
    painter.drawRect(QRectF(0,0,60,60));
    painter.drawText(QPointF(2,12),"Image");
}


void Image::setImage(QImage image)
{
    this->image = image;
    bounds = image.rect();
    prepareGeometryChange();
    ui->getActivePage()->addItem(this);
}


QRectF Image::boundingRect() const
{
    return bounds;
}


void Image::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setRenderHint(QPainter::Antialiasing,true);
    painter->drawImage(image.rect(),image);

    if(isSelected()){
        painter->setPen(QPen(QColor(0,0,255),3));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(bounds);
    }
}


void Image::serializeRead(QDataStream &in)
{

}


void Image::serializeWrite(QDataStream &out)
{

}
