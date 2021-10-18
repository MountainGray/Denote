#ifndef PENSTROKE_H
#define PENSTROKE_H

#include "Framework/bezier.h"
#include "Graphics/pageitem.h"

class PenStroke : public PageItem
{
public:
    PenStroke();

public:
    void initialize(BezierPoint p);
    void append(BezierPoint p);
    void terminate(BezierPoint p);
    void setClipping(QRectF clip_rect = QRectF());

public:
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    int type() const override {return TypePenStroke;}
    //void setDisplayMode(IColor::DisplayMode display_mode) override;
    void serializeRead(QDataStream &in) override;
    void serializeWrite(QDataStream &out) override;

private:
    void calculateShape();

private:
    Bezier bezier;
    QRectF bounds;
    QPainterPath outline;

    QRectF clip_rect;
    bool clipping = false;

    const int line_resolution = 40; //length of drawn lines in pixels
};

#endif // PENSTROKE_H
