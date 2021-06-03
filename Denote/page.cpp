#include "page.h"

Page::Page() : QGraphicsItem(){
    width = 850;
    height = 1100;
}


QRectF Page::boundingRect() const{
    return QRectF(0,0,width,height);
}


void Page::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->setPen(QPen(QColor("white"),2));
    painter->setBrush(QBrush(QColor("white")));
    painter->drawRect(QRect(0,0,width,height));

    if(type == Lines) paintLines(painter);
    else if(type == LinesMargin) paintLinesMargin(painter);
    else if(type == Engineering) paintEngineering(painter);
    else if(type == Graph) paintEngineering(painter);
    else if(type == Staves) paintEngineering(painter);
    else if(type == Custom) paintLinesMargin(painter);
    else paintLinesMargin(painter);

    painter->setPen(QPen(QColor("black"),2));
    painter->setBrush(QBrush(QColor("black")));

    float hole_x = 0.03*width;
    float hole_size = 0.032*width;
    painter->drawEllipse(hole_x, 0.12*height, hole_size, hole_size);
    painter->drawEllipse(hole_x, 0.5*height, hole_size, hole_size);
    painter->drawEllipse(hole_x, 0.88*height, hole_size, hole_size);
}


void Page::paintLines(QPainter *painter){
    painter->setPen(QPen(QColor(43,167,255,150),2));
    for(int line = height/10; line < 20*height/21; line += height/40){
        painter->drawLine(QLineF(0,line,width,line));
    }
}


void Page::paintLinesMargin(QPainter *painter){
    paintLines(painter);
    painter->setPen(QPen(QColor(255,50,43,150),2));
    painter->drawLine(QLineF(width/8,0,width/8,height));
}


void Page::paintEngineering(QPainter *painter){
    int minor_size = 20;//in pixels
    int major_minor = 5;
    int major_size = minor_size*major_minor;

    float h_majors = (width/major_size)-1;
    float v_majors = (height/major_size)-1;
    float h_excess = width - (h_majors*major_size);
    float v_excess = height - (v_majors*major_size);

    float left = 0.6*h_excess;
    float right = width - 0.4*h_excess;
    float top = v_excess/2;
    float bottom = height-v_excess/2;

    painter->setPen(QPen(QColor(56,171,87,255),2));
    painter->drawLine(QLineF(left,top,left,bottom));//left margin
    painter->drawLine(QLineF(right,top,right,bottom));//right margin
    painter->drawLine(QLineF(0,top,width,top));//top margin
    painter->drawLine(QLineF(width*6/17,0,width*6/17, top));//title left
    painter->drawLine(QLineF(width*11/17,0,width*11/17, top));//title right

    painter->setPen(QPen(QColor(56,171,87,100),2));
    for(int i = 0; i <= v_majors; i ++){//major horizontal lines
        painter->drawLine(QLineF(left,top+i*major_size,right,top+i*major_size));
    }
    for(int i = 0; i < h_majors; i ++){//major vertical lines
        painter->drawLine(QLineF(left+i*major_size,top,left+i*major_size,bottom));
    }

    painter->setPen(QPen(QColor(56,171,87,100),1));
    for(int i = 0; i < v_majors*major_minor; i ++){//minor horizontal lines
        if(i%major_minor) painter->drawLine(QLineF(left,top+i*minor_size,right,top+i*minor_size));
    }
    for(int i = 0; i < h_majors*major_minor; i ++){//minor vertical lines
        if(i%major_minor) painter->drawLine(QLineF(left+i*minor_size,top,left+i*minor_size,bottom));
    }
}


void Page::paintGraph(QPainter *painter){
    return;
}


void Page::paintStaves(QPainter *painter){
    return;
}


void Page::paintCustom(QPainter *painter){
    return;
}
