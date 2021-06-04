#include "Tools/stroke.h"
#include "Tools/pen.h"
#include <QDebug>

Stroke::Stroke(Pen* pen)
{
   this->pen = pen;
   color = QColor(Qt::black);

   /*
   points.append(QPointF(25,25));
   points.append(QPointF(250,700));
   points.append(QPointF(500,500));

   QRectF dirty = QRectF(QPointF(25,25),QPointF(500,500)).normalized();
   update(dirty);
   */
}


void Stroke::init(QGraphicsSceneMouseEvent *event)
{
    //return;
    points.append(event->scenePos());
}


void Stroke::addpoint(QGraphicsSceneMouseEvent *event)
{
    //return;
    if(count < 6){
        count ++;
    }
    else {
        count = 0;
        if(points.size() > 2){
            if(points.size()%2 == 1){
                /*
                points.pop_back();
                float avg_x = (points.last().x() + event->scenePos().x())/2;
                float avg_y = (points.last().y() + event->scenePos().y())/2;
                points.append(QPointF(avg_x,avg_y));
                */
            }
            QRectF dirty = QRectF(event->scenePos(),points.last()).normalized();
            update(dirty);
        }
        points.append(event->scenePos());
    }


}


void Stroke::finish(QGraphicsSceneMouseEvent *event)
{
    //return;
    points.append(event->scenePos());
}


void Stroke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPen pen = QPen(color, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
    painter->setPen(pen);

    QPointF p0,p1,p2;
    float t, last_x, last_y, new_x, new_y = 0;

    for(int i = 0; i < points.size()-2; i += 2){
        p0 = points.at(i);
        p1 = points.at(i+1);
        p2 = points.at(i+2);

        last_x = p0.x();
        last_y = p0.y();

        for(int j = 1; j <= 10; j++){//5 segments
            t = 0.1*j;
            new_x = powf((1-t),2)*p0.x()+2*(1-t)*t*p1.x()+powf(t,2)*p2.x();
            new_y = powf((1-t),2)*p0.y()+2*(1-t)*t*p1.y()+powf(t,2)*p2.y();

            if(j == 1) painter->setPen(QPen(QColor("red")));
            else if (j == 2) painter->setPen(QPen(QColor("orange")));
            else if (j == 3) painter->setPen(QPen(QColor("yellow")));
            else if (j == 4) painter->setPen(QPen(QColor("green")));
            else if (j == 5) painter->setPen(QPen(QColor("blue")));
            else if (j == 6) painter->setPen(QPen(QColor("purple")));
            else if (j == 7) painter->setPen(QPen(QColor("pink")));
            else if (j == 8) painter->setPen(QPen(QColor("brown")));
            else if (j == 9) painter->setPen(QPen(QColor("grey")));
            else painter->setPen(QPen(QColor("black")));

            //qDebug() << p0.x() << p1.x() << p2.x() << new_x;

            painter->drawLine(last_x, last_y, new_x, new_y);

            last_x = new_x;
            last_y = new_y;
        }
    }
}


QRectF Stroke::boundingRect() const{
    return QRectF(-1000,-1000,2000,2000);
}
