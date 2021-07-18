#include "fillstroke.h"
#include "Tools/fill.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>


FillStroke::FillStroke(Fill* fill)
{
    color = fill->getColor();
    painter_pen = QPen(color,3,Qt::SolidLine, Qt::RoundCap);
    painter_brush = QBrush(color);
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);
}


void FillStroke::init(QPointF pos)
{
    points.append(pos);
    bounds = QRectF(pos.x(),pos.y(),0,0);
}


void FillStroke::addpoint(QPointF pos)
{
    updateBounds(pos);
    if(points.size() > 2){
        if(points.size()%2 == 1){
            points.pop_back();
            float avg_x = (points.last().x() + pos.x())/2;
            float avg_y = (points.last().y() + pos.y())/2;
            points.append(QPointF(avg_x,avg_y));
        }
        QRectF new_area = QRectF(pos,points.last());
        QRectF old_area = QRectF(points.last(),points.at(points.size()-2));
        points.append(pos);
        update(new_area.united(old_area).adjusted(-1,-1,1,1));
    } else {
        points.append(pos);
    }
}

void FillStroke::finish(QPointF pos)
{
    if(points.size() > 2){
        updateBounds(pos);
        QRectF new_area = QRectF(pos,points.last());
        QRectF old_area = QRectF(points.last(),points.at(points.size()-2));
        points.append(pos);
        update(new_area.united(old_area).adjusted(-1,-1,1,1));
    }
}


QRectF FillStroke::boundingRect() const{
    return bounds;
}


QPainterPath FillStroke::shape() const
{
    QPainterPath path;
    if(points.length() > 0){
        path.moveTo(points.first());
    }
    foreach(QPointF point, points){
        path.lineTo(point);
    }
    return path;
}


void FillStroke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    float world_scale = option->levelOfDetailFromTransform(painter->worldTransform());
    int line_res = qBound(5, qRound(4*world_scale), 200); //lines per bezier curve

    QPointF p0,p1,p2;
    float t, new_x, new_y;
    QPolygonF poly;

    painter->setPen(painter_pen);
    painter->setBrush(painter_brush);

    for(int i = 0; i < points.size()-2; i += 2){
        p0 = points.at(i);
        p1 = points.at(i+1);
        p2 = points.at(i+2);


        if(QGraphicsItem::isSelected()){
            //QColor(((i%4)+1)*80,(i%4)*21,(i%4)*127)// false color
            painter_pen.setColor(color.darker());
            painter->setPen(painter_pen);
        } else {
            painter_pen.setColor(color);
            painter->setPen(painter_pen);
        }



        for(int j = 1; j <= line_res; j++){//5 segments
            t = j/float(line_res);

            new_x = (1-t)*(1-t)*p0.x()+2*(1-t)*t*p1.x()+t*t*p2.x();
            new_y = (1-t)*(1-t)*p0.y()+2*(1-t)*t*p1.y()+t*t*p2.y();

            poly << QPointF(new_x,new_y);
        }
    }
    if(points.size() > 2 and points.size()%2 == 0){
        poly << points.last();
    }

    painter->drawPolygon(poly);
}


void FillStroke::updateBounds(QPointF point)
{
    float padding = 1;
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
