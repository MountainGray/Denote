#ifndef IMAGE_H
#define IMAGE_H

#include "Tools/tool.h"

#include <QGraphicsItem>

class UI;

class Image : public QGraphicsItem, public Tool
{
public:
    Image(UI* ui);

public:
    void paintPreset(QPaintEvent *event) override;
    void setImage(QImage image);

    void activate() override{};
    void deactivate() override{};

public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    int type() const override {return TypeImage;}

private:
    QRectF bounds;
    QImage image;

};

#endif // IMAGE_H
