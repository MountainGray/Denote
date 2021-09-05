#include "icolor.h"


IColor::IColor(QColor color, DisplayMode mode){
    normal_color = color;
    setDisplayMode(mode);
    if(mode != Normal){
        normal_color = active_color;
        setDisplayMode(mode);
    }
}


QColor IColor::inverted()
{
    QColor i = normal_color;
    i.setHsl(i.hslHue(),i.hslSaturation(),255-i.lightness(),i.alpha());
    return i;
}


void IColor::setDisplayMode(DisplayMode mode)
{
    if(mode == Normal) active_color = normal_color;
    else if(mode == Inverted) active_color = inverted();
    else active_color = normal_color;

    display_mode = mode;
}
