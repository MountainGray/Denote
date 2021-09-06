#include "bezier.h"
#include <QtDebug>


Bezier::Bezier()
{

}


void Bezier::appendPoint(BezierPoint p)
{
    if(points.isEmpty()){
        distances.append(0);
    } else {
        BezierPoint l = points.last();
        distances.append(abs(p.x-l.x)+abs(p.y-l.y));
    }

    points.append(p);
    max_base = int((points.count()-1)/3)*3;
}


BezierPoint Bezier::getFirst() const
{
    return points.first();
}


BezierPoint Bezier::getLast() const
{
    return points.last();
}


BezierPoint Bezier::getPointAt(int i) const
{
    if(i < 0) return points.at(points.count()+i);
    return points.at(i);
}


void Bezier::setPointAt(int i, BezierPoint p)
{
    if(i < 0) points.replace(points.count()+i,p);
    else points.replace(i,p);
}


BezierPoint Bezier::interpolateAt(float t)
{
    if(t >= max_base){
        if(t < points.count()) return getPointAt(t);
        qDebug() << "Parameter outside of interpretable range";
        return BezierPoint();
    }

    int base = int(t/3)*3;

    BezierPoint p, p0, p1, p2, p3;
    p0 = getPointAt(base);
    p1 = getPointAt(base+1);
    p2 = getPointAt(base+2);
    p3 = getPointAt(base+3);

    t = (t-base)/3;
    float i = 1-t;

    p.x = i*i*i*p0.x+3*i*i*t*p1.x+3*i*t*t*p2.x+t*t*t*p3.x;
    p.y = i*i*i*p0.y+3*i*i*t*p1.y+3*i*t*t*p2.y+t*t*t*p3.y;
    p.t = i*i*i*p0.t+3*i*i*t*p1.t+3*i*t*t*p2.t+t*t*t*p3.t;

    return p;
}


float Bezier::getDistanceAt(int i) const
{
    if(i >= distances.count() or i < 0){
        qDebug() << "Distance index out of range";
        return -1;
    }

    return distances.at(i);
}
