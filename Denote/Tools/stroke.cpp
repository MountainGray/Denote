#include "Tools/stroke.h"
#include "Tools/pen.h"
#include <QDebug>
#include <QPainter>

Stroke::Stroke(Pen* pen)
{
   this->pen = pen;
   color = QColor(Qt::black);
}


void Stroke::init(QPointF pos, float pressure)
{
    points.append(PressurePoint(pos,pressure));
}


void Stroke::addpoint(QPointF pos, float pressure)
{
    if(count < 2){
        count ++;
    }
    else {
        count = 0;
        if(points.size() > 2){
            if(points.size()%2 == 1){
                points.pop_back();
                float avg_x = (points.last().x() + pos.x())/2;
                float avg_y = (points.last().y() + pos.y())/2;
                points.append(PressurePoint(avg_x,avg_y,pressure));
            }
            QRectF new_area = QRectF(pos,points.last());
            QRectF old_area = QRectF(points.last(),points.at(points.size()-2));
            points.append(PressurePoint(pos,pressure));
            update(new_area.united(old_area).adjusted(-10,-10,10,10));
        } else {
            points.append(PressurePoint(pos,pressure));
        }
    }
}


void Stroke::finish(QPointF pos, float pressure)
{
    if(points.size() > 2){
        QRectF new_area = QRectF(pos,points.last());
        QRectF old_area = QRectF(points.last(),points.at(points.size()-2));
        points.append(PressurePoint(pos,pressure));
        update(new_area.united(old_area).adjusted(-10,-10,10,10));
    }
}


void Stroke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    float res = 15;

    QPen pen = QPen(color, 3);
    pen.setCosmetic(true);
    painter->setPen(pen);

    PressurePoint p0,p1,p2;
    float t, p, last_x, last_y, new_x, new_y;
    QLineF line;

    for(int i = 0; i < points.size()-2; i += 2){
        p0 = points.at(i);
        p1 = points.at(i+1);
        p2 = points.at(i+2);

        last_x = p0.x();
        last_y = p0.y();

        //pen.setColor(QColor(rand()%255,rand()%255,rand()%255,255)); //display each bezier as random color

        for(int j = 1; j <= res; j++){//5 segments
            t = j/res;

            new_x = (1-t)*(1-t)*p0.x()+2*(1-t)*t*p1.x()+t*t*p2.x();
            new_y = (1-t)*(1-t)*p0.y()+2*(1-t)*t*p1.y()+t*t*p2.y();

            line = QLineF(last_x, last_y, new_x, new_y);
            p = p0.getPressure()*(1-t) + p2.getPressure()*t;
            pen.setWidthF(pressureToWidth(p));

            painter->setPen(pen);
            painter->drawLine(line);

            last_x = new_x;
            last_y = new_y;
        }
    }
    if(points.size() > 2 and points.size()%2 == 0){
        painter->drawLine(points.at(points.size()-2), points.last());
    }
}


float Stroke::pressureToWidth(float pressure)
{
    return pressure * 10 + 1;
}


QRectF Stroke::boundingRect() const{
    return QRectF(-1000,-1000,2000,2000);
}
