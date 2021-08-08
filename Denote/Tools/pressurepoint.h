#ifndef PRESSUREPOINT_H
#define PRESSUREPOINT_H

#include <QPointF>
#include "Framework/serializable.h"

class PressurePoint : public QPointF, public Serializable
{
public:
    PressurePoint();
    PressurePoint(QPointF point, float pressure = 0);
    PressurePoint(qreal x_pos, qreal y_pos, float pressure = 0);

public:
    float p(){ return pressure; }
    void setP(float pressure){ this->pressure = pressure; }
    void serializeRead(QDataStream &in) override;
    void serializeWrite(QDataStream &out) override;

private:
    float pressure;
};

#endif // PRESSUREPOINT_H
