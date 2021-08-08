#include "pressurepoint.h"


PressurePoint::PressurePoint()
{
    pressure = 0;
}


PressurePoint::PressurePoint(QPointF point, float pressure) : QPointF(point)
{
    this->pressure = pressure;
}


PressurePoint::PressurePoint(qreal x_pos, qreal y_pos, float pressure) : QPointF(x_pos, y_pos)
{
    this->pressure = pressure;
}


void PressurePoint::serializeRead(QDataStream &in)
{
    float x, y, p;
    in >> x >> y >> p;
    setX(x);
    setY(y);
    setP(p);
}


void PressurePoint::serializeWrite(QDataStream &out)
{
    out << x();
    out << y();
    out << p();
}
