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
    path = QPainterPath(event->scenePos());
}

void Stroke::addpoint(QGraphicsSceneMouseEvent *event)
{
    QRectF dirty = QRectF(event->scenePos(),points.last()).normalized();
    update(dirty);
    //qDebug() << event->scenePos();
    points.append(event->scenePos());
    //qDebug("Add point");
    if((points.size()>=7) and (points.size()%3 ==1)){
        int shiftpoint = points.size() - 4;
        qDebug() << shiftpoint;
        points.insert(shiftpoint,
                              (points.at(shiftpoint-1)+ points.at(shiftpoint+1))/2
                      );
        path.cubicTo(points.at(shiftpoint-2),points.at(shiftpoint-1),points.at(shiftpoint));
    }


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
    painter->drawPath(path);
    /*
    if(points.size()>=1){
        if(points.size()>4){
            for(int i = 3; i <points.size()-3;i+=3){
                points.insert(i,
                              (points.at(i+1)+ points.at(i-1))/2
                              );
            }
           for(int i = 0; i+3<points.size()-1;i+=3){
                path.cubicTo(points.at(i+1),points.at(i+2),points.at(i+3));
           }
        }
    */
    this->show();
}

QRectF Stroke::boundingRect() const{
    return QRectF(-1000,-1000,2000,2000);
}
