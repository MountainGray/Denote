#ifndef IMAGE_H
#define IMAGE_H

#include "Tools/tool.h"
#include "Graphics/pageitem.h"

class UI;

class Image : public PageItem, public Tool
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
    void serializeRead(QDataStream &in) override;
    void serializeWrite(QDataStream &out) override;

private:
    QRectF bounds;
    QImage image;

};

#endif // IMAGE_H
