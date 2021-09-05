#ifndef ICOLOR_H
#define ICOLOR_H

#include <QColor>

class IColor
{

public:
    enum DisplayMode{Normal, Inverted};

    IColor(QColor color = QColor(), DisplayMode mode = Normal);

public:
    QColor normalColor(){return normal_color;}
    QColor active(){return active_color;}
    QColor inverted();
    void setDisplayMode(DisplayMode mode);

private:
    QColor normal_color;
    QColor active_color;
    DisplayMode display_mode;
};

#endif // ICOLOR_H
