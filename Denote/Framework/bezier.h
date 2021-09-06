#ifndef BEZIER_H
#define BEZIER_H

//Bezier structure that holds x, y, and thickness.
struct BezierPoint
{
    float x;
    float y;
    float t;
};



#include <QList>

//Cubic Bezier class
class Bezier
{
public:
    Bezier();

public:
    void appendPoint(BezierPoint p);
    BezierPoint getFirst() const;
    BezierPoint getLast() const;
    BezierPoint getPointAt(int i) const;
    void setPointAt(int i, BezierPoint p);
    BezierPoint interpolateAt(float t);

    int count() const {return points.count();}
    int maxBase() const {return max_base;}

    float getDistanceAt(int i) const;

private:
    QList<BezierPoint> points;
    QList<float> distances;
    int max_base = 0;
};

#endif // BEZIER_H
