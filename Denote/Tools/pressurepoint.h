#ifndef PRESSUREPOINT_H
#define PRESSUREPOINT_H

#include <QPointF>

class PressurePoint : public QPointF
{
public:
    PressurePoint();
    PressurePoint(QPointF point, float pressure = 0);
    PressurePoint(qreal x_pos, qreal y_pos, float pressure = 0);

public:
    float p(){ return pressure; }
    void setP(float pressure){ this->pressure = pressure; }

private:
    float pressure;
};

#endif // PRESSUREPOINT_H
