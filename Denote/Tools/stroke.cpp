#include "Tools/stroke.h"
#include "Tools/pen.h"
#include <QDebug>

Stroke::Stroke(Pen* pen)
{
   this->pen = pen;
}

void Stroke::init(QGraphicsSceneMouseEvent *event)
{
    qDebug("start");
    points.append(event->scenePos());
}

void Stroke::addpoint(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->scenePos();
    points.append(event->scenePos());
    qDebug("Add point");
    QRectF dirty = QRectF(points.first(),points.last()).normalized();
    update(dirty);


}

void Stroke::finish(QGraphicsSceneMouseEvent *event)
{
    points.append(event->scenePos());
}

void Stroke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    color = QColor(Qt::black);
    QPen pen = QPen(color, 0, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    pen.setCosmetic(true);
    painter->setPen(pen);

    if(points.size()>1){
        for(int i = 1; i < points.size()-1; i++){
        painter->drawLine(points.at(i-1),points.at(i));
        }
    }
    this->show();

}

QRectF Stroke::boundingRect() const{
    return QRectF(-1000,-1000,2000,2000);
}
