#ifndef ICOLOR_H
#define ICOLOR_H

#include <QColor>

class IColor : public QColor
{
public:
    IColor();
    IColor(QColor q);
    IColor(int r, int g, int b, int a = 255);

public:
    void invertBrightness();
};

#endif // ICOLOR_H
