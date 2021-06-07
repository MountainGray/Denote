#include "Tools/stroke.h"
#include "Tools/pen.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


Stroke::Stroke(Pen* pen)
{
   this->pen = pen;
   color = QColor(Qt::black);
}


void Stroke::init(QPointF pos, float pressure)
{
    points.append(PressurePoint(pos,pressure));
    bounds = QRectF(pos.x()-1, pos.y()-1, 2, 2);
}


void Stroke::addpoint(QPointF pos, float pressure)
{
    if(count < 2){
        count ++;
    }
    else {
        updateBounds(pos);
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
        count = 0;
    }
}


void Stroke::finish(QPointF pos, float pressure)
{
    if(points.size() > 2){
        updateBounds(pos);
        QRectF new_area = QRectF(pos,points.last());
        QRectF old_area = QRectF(points.last(),points.at(points.size()-2));
        points.append(PressurePoint(pos,pressure));
        update(new_area.united(old_area).adjusted(-10,-10,10,10));
    }
}


QRectF Stroke::boundingRect() const{
    return bounds;
}


void Stroke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    float world_scale = option->levelOfDetailFromTransform(painter->worldTransform());
    int line_res = qBound(5, qRound(4*world_scale), 200); //lines per bezier curve


    QPen pen = QPen(color, 3, Qt::SolidLine, Qt::RoundCap);
    //pen.setCosmetic(true);
    painter->setPen(pen);

    PressurePoint p0,p1,p2;
    float t, last_x, last_y, new_x, new_y, new_p;
    QLineF line;

    for(int i = 0; i < points.size()-2; i += 2){
        p0 = points.at(i);
        p1 = points.at(i+1);
        p2 = points.at(i+2);

        last_x = p0.x();
        last_y = p0.y();

        //pen.setColor(QColor(rand()%255,rand()%255,rand()%255,255)); //display each bezier as random color

        for(int j = 1; j <= line_res; j++){//5 segments
            t = j/float(line_res);

            new_x = (1-t)*(1-t)*p0.x()+2*(1-t)*t*p1.x()+t*t*p2.x();
            new_y = (1-t)*(1-t)*p0.y()+2*(1-t)*t*p1.y()+t*t*p2.y();
            new_p = (1-t)*(1-t)*p0.p()+2*(1-t)*t*p1.p()+t*t*p2.p();

            //pen.setColor(QColor(rand()%255,rand()%255,rand()%255,255)); //display each bezier as random color

            line = QLineF(last_x, last_y, new_x, new_y);
            pen.setWidthF(pressureToWidth(new_p));
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
    return pressure * 2 + 0.2;
}


void Stroke::updateBounds(PressurePoint point)
{
    float padding = 5;
    bool changed = false;
    if(point.x() < bounds.left()+padding){
        bounds.setLeft(point.x()-padding);
        changed = true;
    }
    if(point.x() > bounds.right()-padding){
        bounds.setRight(point.x()+padding);
        changed = true;
    }
    if(point.y() < bounds.top()+padding){
        bounds.setTop(point.y()-padding);
        changed = true;
    }
    if(point.y() > bounds.bottom()-padding){
        bounds.setBottom(point.y()+padding);
        changed = true;
    }
    if(changed){
        prepareGeometryChange();
    }
}
