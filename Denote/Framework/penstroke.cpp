#include "penstroke.h"
#include <QPainter>


PenStroke::PenStroke()
{
    setFlag(GraphicsItemFlag::ItemIsSelectable, true);

    //setCacheMode(CacheMode::DeviceCoordinateCache);
}


void PenStroke::initialize(BezierPoint p)
{
    //set initial point and bounds
    bezier.appendPoint(p);
    bounds = QRectF(p.x-p.t/2, p.y-p.t/2, p.t, p.t);
    //prepareGeometryChange();
}


void PenStroke::append(BezierPoint p)
{
    //add point and update bounds
    bezier.appendPoint(p);
    QRectF new_bounds = QRectF(p.x-p.t/2, p.y-p.t/2, p.t, p.t);
    bounds = bounds.united(new_bounds);
    //prepareGeometryChange();

    //set connection points tangent when applicable
    if(bezier.count()%3 == 2 and bezier.count() != 2){
        BezierPoint p0 = bezier.getPointAt(-3);
        BezierPoint p1;
        p1.x = (p.x+p0.x)/2;
        p1.y = (p.y+p0.y)/2;
        p1.t = (p.t+p0.t)/2;
        bezier.setPointAt(-2,p1);
    }

    /*
    //testing
    if(bezier.count() > 50){
        BezierPoint f = bezier.getPointAt(-50);
        f.x = 0;
        f.y = 0;
        bezier.setPointAt(-50,f);
    }
    */
}


void PenStroke::terminate(BezierPoint p)
{
    if(bezier.count() <= 1) return;

    while(bezier.count()%3 != 0) bezier.appendPoint(p); //ensures last curve of bezier is completed
    bezier.appendPoint(p);

    QRectF new_bounds = QRectF(p.x-p.t/2, p.y-p.t/2, p.t, p.t);
    bounds = bounds.united(new_bounds);

    prepareGeometryChange();
    calculateShape();
}


void PenStroke::setClipping(QRectF clip_rect)
{
    this->clip_rect = clip_rect;
    clipping = !clip_rect.isNull();
}


QRectF PenStroke::boundingRect() const
{
    return bounds;
}


QPainterPath PenStroke::shape() const
{
    return outline;
}


void PenStroke::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);
    if(bezier.count() == 0) return;

    //if(clipping) painter->setClipRect(clip_rect);

    QPen pen = QPen(QColor("red"),1,Qt::PenStyle::SolidLine,Qt::PenCapStyle::RoundCap,Qt::RoundJoin);
    BezierPoint p0, p1;
    p0 = bezier.getFirst();
    float world_scale = option->levelOfDetailFromTransform(painter->worldTransform());
    float avg_dist = 0, t = 0.02;

    while(t < bezier.count()){
        p1 = bezier.interpolateAt(t);

        //update line style
        pen.setWidthF(p1.t);
        painter->setPen(pen);
        painter->drawLine(QLineF(p0.x, p0.y, p1.x, p1.y));
        p0 = p1;

        //increment t to maintain line resolution regardless of point density
        //avg_dist = (avg_dist+fmax(bezier.getDistanceAt(t),10))/2;
        //t += fmax(0.4,fmin(line_resolution/(avg_dist*world_scale),3));
        t += 0.5;
        if(t > bezier.count()) t = bezier.count();
    }


    /*
    //paint handles
    painter->setBrush(Qt::NoBrush);

    for(int i = 0; i < bezier.count(); i++){
        if(i%3 == 0) painter->setPen(QPen(QColor("blue"),0,Qt::PenStyle::SolidLine,Qt::PenCapStyle::RoundCap,Qt::RoundJoin));
        else painter->setPen(QPen(QColor("red"),0,Qt::PenStyle::SolidLine,Qt::PenCapStyle::RoundCap,Qt::RoundJoin));

        BezierPoint p = bezier.getPointAt(i);
        painter->drawEllipse(p.x-2,p.y-2,4,4);
    }
    */


}


void PenStroke::serializeRead(QDataStream &in)
{
    /*
    PageItem::serializeRead(in);

    qsizetype num_points;
    in >> num_points;
    points.clear();
    for(qsizetype i = 0; i < num_points; i++){
        PressurePoint p;
        p.serializeRead(in);
        points.push_back(p);
    }
    in >> painter_pen;
    in >> bounds;
    in >> width;
    QColor normal;
    in >> normal;
    color = IColor(normal);
    update();
    */
}


void PenStroke::serializeWrite(QDataStream &out)
{
    /*
    PageItem::serializeWrite(out);

    out << points.length();
    foreach(PressurePoint point, points){
        point.serializeWrite(out);
    }
    out << painter_pen;
    out << bounds;
    out << width;
    out << color.normalColor();
    */
}


void PenStroke::calculateShape()
{
    QPainterPath path;
    BezierPoint p;
    if(bezier.count() > 0){
        p = bezier.getFirst();
        path.moveTo(QPointF(p.x,p.y));
    }
    for(int i = 0; i < bezier.count(); i++){
        p = bezier.getPointAt(i);
        path.lineTo(QPointF(p.x,p.y));
    }
    QPainterPathStroker path_stroke;
    path_stroke.setWidth(1);
    outline = path_stroke.createStroke(path);
}
