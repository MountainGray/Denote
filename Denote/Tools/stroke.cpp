#include "Tools/stroke.h"
#include "Tools/pen.h"
#include <QDebug>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>


Stroke::Stroke(Pen* pen)
{
    color = pen->getColor();
    width = pen->getWidth();
    painter_pen = QPen(color.active(), width, Qt::SolidLine, Qt::RoundCap);
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
}


Stroke::Stroke(Stroke *stroke)
{
    color = IColor(stroke->color);
    width = stroke->width;
    points = stroke->points;
    bounds = stroke->bounds;
    painter_pen = stroke->painter_pen;
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
    setTransform(stroke->transform());
    setPos(stroke->pos());
    setRotation(stroke->rotation());
    setScale(stroke->scale());
}


void Stroke::init(QPointF pos, float pressure)
{
    points.append(PressurePoint(pos,pressure));
    bounds = QRectF(pos.x()-width/2, pos.y()-width/2, width, width);
}


void Stroke::addpoint(QPointF pos, float pressure)
{
    updateBounds(pos);
    if(points.size() > 2){
        if(points.size()%2 == 1){
            points.pop_back();
            float avg_x = (points.last().x() + pos.x())/2;
            float avg_y = (points.last().y() + pos.y())/2;
            float avg_p = (points.last().p() + pressure)/2;
            points.append(PressurePoint(avg_x,avg_y,avg_p));
        }
        QRectF new_area = QRectF(pos,points.last());
        QRectF old_area = QRectF(points.last(),points.at(points.size()-2));
        points.append(PressurePoint(pos,pressure));
        update(new_area.united(old_area).adjusted(-width,-width,width,width));
    } else {
        points.append(PressurePoint(pos,pressure));
    }
}


void Stroke::finish(QPointF pos, float pressure)
{
    if(points.size() > 2){
        updateBounds(pos);
        QRectF new_area = QRectF(pos,points.last());
        QRectF old_area = QRectF(points.last(),points.at(points.size()-2));
        points.append(PressurePoint(pos,pressure));
        update(new_area.united(old_area).adjusted(-width,-width,width,width));
    }
}


QRectF Stroke::boundingRect() const{
    return bounds;
}


QPainterPath Stroke::shape() const
{
    QPainterPath path;
    if(points.length() > 0){
        path.moveTo(points.first());
    }
    foreach(QPointF point, points){
        path.lineTo(point);
    }
    QPainterPathStroker path_stroke;
    path_stroke.setWidth(width);
    return path_stroke.createStroke(path);
}


void Stroke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    float world_scale = option->levelOfDetailFromTransform(painter->worldTransform());
    int line_res = qBound(5, qRound(4*world_scale), 200); //lines per bezier curve

    PressurePoint p0,p1,p2;
    float t, last_x, last_y, new_x, new_y, new_p;
    QLineF line;

    //QColor(((i%4)+1)*80,(i%4)*21,(i%4)*127); //false color

    for(int o = 0; o < 2; o++){
        if(o == 0){
            if(QGraphicsItem::isSelected()) painter_pen.setColor(color.active().darker(250));
            else painter_pen.setColor(color.active());
        } else {
            if(QGraphicsItem::isSelected()) painter_pen.setColor(color.active());
            else return;
        }

        for(int i = 0; i < points.size()-2; i += 2){
            p0 = points.at(i);
            p1 = points.at(i+1);
            p2 = points.at(i+2);

            last_x = p0.x();
            last_y = p0.y();

            for(int j = 1; j <= line_res; j++){//5 segments
                t = j/float(line_res);

                new_x = (1-t)*(1-t)*p0.x()+2*(1-t)*t*p1.x()+t*t*p2.x();
                new_y = (1-t)*(1-t)*p0.y()+2*(1-t)*t*p1.y()+t*t*p2.y();
                new_p = (1-t)*(1-t)*p0.p()+2*(1-t)*t*p1.p()+t*t*p2.p();

                line = QLineF(last_x, last_y, new_x, new_y);

                if(QGraphicsItem::isSelected() and o == 0) painter_pen.setWidthF(new_p+2);
                else painter_pen.setWidthF(new_p);

                painter->setPen(painter_pen);
                painter->drawLine(line);

                last_x = new_x;
                last_y = new_y;
            }
        }
        if(points.size() > 2 and points.size()%2 == 0){
            painter->drawLine(points.at(points.size()-2), points.last());
        }
    }
}


void Stroke::setDisplayMode(IColor::DisplayMode display_mode)
{
    color.setDisplayMode(display_mode);
}


void Stroke::updateBounds(PressurePoint point)
{
    float padding = width;
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
