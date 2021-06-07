#include "pressurepoint.h"


PressurePoint::PressurePoint() : QPointF()
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
