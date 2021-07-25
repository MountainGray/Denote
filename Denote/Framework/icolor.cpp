#include "icolor.h"


IColor::IColor(){

}


IColor::IColor(QColor q) : QColor(q)
{

}


IColor::IColor(int r, int g, int b, int a) : QColor(r,g,b,a)
{

}


void IColor::invertBrightness()
{
    setHslF(hueF(),saturationF(),1.0-lightnessF(),alphaF());
}
